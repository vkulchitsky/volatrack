#include "renderer.h"
#include "spheremesh.hpp"

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QMouseEvent>

using Byte = unsigned char; // standard sais that sizeof(char) == 1
using Size = decltype(sizeof(void*)); // native size_t

//! static storage enought to hold the object of the given type
template<class C, Size Align = alignof(C)>
struct StaticBuf { alignas(Align) static Byte data[ sizeof(C) ]; };

template<class C, Size Align>
alignas(Align) Byte StaticBuf<C, Align>::data[ sizeof(C) ] = {};

inline void* addOffset(void* ptr, Size n)
{
    // is this even possible?
    static_assert(sizeof(Byte) == 1, "can`t apply offset...");

    return static_cast<void*>( static_cast<Byte*>(ptr) + n );
}

template<class C>
constexpr Byte* b_ptr_(C* ptr) { return reinterpret_cast<Byte*>(ptr); }

//! returns offset of member of the class
template<class C, class M>
Size offsetOfM(M C::*m)
{
    C* ptr = reinterpret_cast<C*>( &StaticBuf<C>::data );
    return Size( b_ptr_(&( ptr->*m )) - b_ptr_(ptr) );
    // TODO: check and clean
    //return Size( (Byte*)&( ptr->*m ) - (Byte*)ptr );
}


const char* vs = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec4 aColor;
    layout (location = 2) in mat4 aInstanceMatrix;

    out vec4 color;
    out vec3 fragPos;

    void main()
    {
        color = aColor;
        fragPos = (aInstanceMatrix * vec4(aPos, 1.0f)).xyz;
        gl_Position = aInstanceMatrix * vec4(aPos, 1.0f);
    }
    )";

const char* gs = R"(
    #version 330 core
    layout (triangles) in;
    layout (triangle_strip, max_vertices = 3) out;

    in vec4 color[];
    in vec3 fragPos[];
    out vec4 o_color;
    out vec3 o_normal;
    out vec3 o_fragPos;

    uniform mat4 projection;
    uniform mat4 view;

    void main()
    {
        o_color = color[0];
        o_fragPos = fragPos[0];
        o_normal = normalize(cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz,
                                   gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz));

        gl_Position = projection * view * gl_in[0].gl_Position;
        EmitVertex();

        gl_Position = projection * view * gl_in[1].gl_Position;
        EmitVertex();

        gl_Position = projection * view * gl_in[2].gl_Position;
        EmitVertex();

        EndPrimitive();
    }
    )";

const char* fs = R"(
    #version 330 core
    in vec4 o_color;
    in vec3 o_normal;
    in vec3 o_fragPos;

    out vec4 FragColor;

    void main()
    {
        vec3 lightColor = vec3(1.0, 1.0, 1.0);
        vec3 lightPos = vec3(100.0f);

        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
        vec3 lightDir = normalize(lightPos - o_fragPos);
        float diff = max(dot(o_normal, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        vec3 result = (ambient + diffuse) * o_color.xyz;
        FragColor = vec4(result, o_color.w);
    }
)";



Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(new QOpenGLShaderProgram)
    , m_bgColor(Qt::lightGray)
    , m_spheresVBO(QOpenGLBuffer::VertexBuffer)
    , m_spheresEBO(QOpenGLBuffer::IndexBuffer)
    , m_opInstanceVBO(QOpenGLBuffer::VertexBuffer)
    , m_transInstanceVBO(QOpenGLBuffer::VertexBuffer)
    , m_opaqueCount(0)
    , m_transCount(0)
    , m_camera(Camera(QVector3D(0.0f, 0.0f, 3.0f)))
{
    setFocusPolicy(Qt::StrongFocus);
}

Renderer::~Renderer()
{
    delete m_program;
    delete m_opaqueVAO;
}

void Renderer::setSpheres(const QVector<RenderSphere> &spheres)
{
    QVector<RenderSphere> opObjs;
    QVector<RenderSphere> transObjs;
    for(const auto& obj : spheres)
    {
        if(obj.color.w() > 0.05)
        {
            if(obj.color.w() >= 1)
            {
                opObjs.push_back(obj);
            }
            else
            {
                transObjs.push_back(obj);
            }
        }
    }

    m_opaqueCount = opObjs.count();
    m_transCount = transObjs.count();

    m_opInstanceVBO.bind();
    m_opInstanceVBO.allocate(opObjs.size() * sizeof(RenderSphere));
    m_opInstanceVBO.write(0, opObjs.data(), opObjs.size() * sizeof(RenderSphere));
    m_opInstanceVBO.release();

    m_transInstanceVBO.bind();
    m_transInstanceVBO.allocate(transObjs.size() * sizeof(RenderSphere));
    m_transInstanceVBO.write(0, transObjs.data(), transObjs.size() * sizeof(RenderSphere));
    m_transInstanceVBO.release();

    update();
}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();

    m_opaqueVAO = new QOpenGLVertexArrayObject(this);
    m_transVAO = new QOpenGLVertexArrayObject(this);

    m_program->create();

    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       vs);
    m_program->addShaderFromSourceCode(QOpenGLShader::Geometry,
                                       gs);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       fs);
    if(!m_program->link())
    {
        m_program->log();
    }

    setupMesh();

    // OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::paintGL()
{
    glClearColor(m_bgColor.redF(), m_bgColor.greenF(), m_bgColor.blueF(),
                 m_bgColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // sort transparent
    m_transInstanceVBO.bind();
    RenderSphere* rsPtr = static_cast<RenderSphere*>(m_transInstanceVBO.map(QOpenGLBuffer::ReadWrite));
    std::vector<RenderSphere> spheres(rsPtr, rsPtr + m_transCount);
    std::sort(spheres.rbegin(), spheres.rend(),
              [this](const RenderSphere& rs1, const RenderSphere& rs2)
    {
        return (m_camera.Position - QVector3D(rs1.model(0,3), rs1.model(1,3), rs1.model(2,3))).length() <
               (m_camera.Position - QVector3D(rs2.model(0,3), rs2.model(1,3), rs2.model(2,3))).length();
    });
    memcpy(rsPtr, spheres.data(), spheres.size() * sizeof(RenderSphere));

    m_transInstanceVBO.unmap();

    m_transInstanceVBO.release();

    m_opaqueVAO->bind();
    m_spheresEBO.bind();

    m_program->bind();

    // pass projection matrix to shader (note that in this case it could change every frame)
    QMatrix4x4 projection;
    projection.setToIdentity();
    projection.perspective((m_camera.Zoom),
                           (float)width() / (float)height(),
                           0.01f, 2000.0f);

    int projLoc = m_program->uniformLocation("projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.data());

    // camera/view transformation
    auto view = m_camera.GetViewMatrix();
    int viewLoc = m_program->uniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());

    glEnable(GL_DEPTH_TEST);

    glDrawElementsInstanced(GL_TRIANGLES, sizeof(GeoIcosInds) / sizeof(unsigned int),
                            GL_UNSIGNED_INT, 0, m_opaqueCount);

    m_program->release();
    m_opaqueVAO->release();
    m_spheresEBO.release();




    m_transVAO->bind();
    m_spheresEBO.bind();

    m_program->bind();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.data());

    // camera/view transformation
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());

    for(unsigned int i = 0; i < m_transCount; ++i)
    {
        glDrawElementsInstancedBaseInstance(
                    GL_TRIANGLES,
                    sizeof(GeoIcosInds) / sizeof(unsigned int),
                    GL_UNSIGNED_INT,
                    0, 1, i);
    }

    m_program->release();
    m_transVAO->release();
    m_spheresEBO.release();
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Renderer::wheelEvent(QWheelEvent *event)
{
    m_camera.ProcessMouseScroll(event->delta() * 1e-2);

    update();
}

void Renderer::keyPressEvent(QKeyEvent *event)
{
    float deltaTime = 1e-2;
    if (event->key() == Qt::Key_W)
        m_camera.ProcessKeyboard(FORWARD, deltaTime);
    if (event->key() == Qt::Key_S)
        m_camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (event->key() == Qt::Key_A)
        m_camera.ProcessKeyboard(LEFT, deltaTime);
    if (event->key() == Qt::Key_D)
        m_camera.ProcessKeyboard(RIGHT, deltaTime);

    update();
}

void Renderer::mousePressEvent(QMouseEvent *event)
{
    float xpos = static_cast<float>(event->x());
    float ypos = static_cast<float>(event->y());

    m_lastX = xpos;
    m_lastY = ypos;
}

void Renderer::mouseMoveEvent(QMouseEvent *event)
{
    float xpos = static_cast<float>(event->x());
    float ypos = static_cast<float>(event->y());

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top

    m_lastX = xpos;
    m_lastY = ypos;

    m_camera.ProcessMouseMovement(xoffset, yoffset);

    update();
}

void Renderer::setupMesh()
{
    m_opInstanceVBO.create();
    m_transInstanceVBO.create();
    m_opaqueVAO->create();
    m_transVAO->create();
    m_spheresVBO.create();
    m_spheresEBO.create();

    m_opaqueVAO->bind();

    m_spheresVBO.bind();
    m_spheresVBO.allocate(&GeoIcosVerts[0],
                          sizeof(GeoIcosVerts));
    m_spheresVBO.release();

    m_spheresEBO.bind();
    m_spheresEBO.allocate(&GeoIcosInds[0][0],
                          sizeof(GeoIcosInds));
    m_spheresEBO.release();

    m_opaqueVAO->release();

    m_opaqueVAO->bind();

    m_spheresEBO.bind();

    m_spheresVBO.bind();
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(GL_FLOAT));
    m_spheresVBO.release();

    int loc = 0;
    int stride = sizeof(RenderSphere);
    int vec4_size = 4 * sizeof(float);
    void* offset = 0;

    m_opInstanceVBO.bind();

    loc = 2;
    m_program->enableAttributeArray(loc + 0);
    glVertexAttribPointer(static_cast<GLuint>(loc + 0), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 0, 1);

    offset = addOffset(offset, vec4_size);
    m_program->enableAttributeArray(loc + 1);
    glVertexAttribPointer(static_cast<GLuint>(loc + 1), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 1, 1);

    offset = addOffset(offset, vec4_size);
    m_program->enableAttributeArray(loc + 2);
    glVertexAttribPointer(static_cast<GLuint>(loc + 2), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 2, 1);

    offset = addOffset(offset, vec4_size);
    m_program->enableAttributeArray(loc + 3);
    glVertexAttribPointer(static_cast<GLuint>(loc + 3), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 3, 1);

    offset = addOffset(0, offsetOfM(&RenderSphere::color));
    loc = 1;
    m_program->enableAttributeArray(loc);
    glVertexAttribPointer(static_cast<GLuint>(loc), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc, 1);

    m_opInstanceVBO.release();

    m_opaqueVAO->release();


    //----


    m_transVAO->bind();

    m_spheresVBO.bind();
    m_spheresVBO.release();

    m_spheresEBO.bind();
    m_spheresEBO.release();

    m_transVAO->release();

    m_transVAO->bind();

    m_spheresEBO.bind();

    m_spheresVBO.bind();
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(GL_FLOAT));
    m_spheresVBO.release();

    loc = 0;
    stride = sizeof(RenderSphere);
    vec4_size = 4 * sizeof(float);
    offset = 0;

    m_transInstanceVBO.bind();

    loc = 2;
    m_program->enableAttributeArray(loc + 0);
    glVertexAttribPointer(static_cast<GLuint>(loc + 0), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 0, 1);

    offset = addOffset(offset, vec4_size);
    m_program->enableAttributeArray(loc + 1);
    glVertexAttribPointer(static_cast<GLuint>(loc + 1), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 1, 1);

    offset = addOffset(offset, vec4_size);
    m_program->enableAttributeArray(loc + 2);
    glVertexAttribPointer(static_cast<GLuint>(loc + 2), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 2, 1);

    offset = addOffset(offset, vec4_size);
    m_program->enableAttributeArray(loc + 3);
    glVertexAttribPointer(static_cast<GLuint>(loc + 3), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc + 3, 1);

    offset = addOffset(0, offsetOfM(&RenderSphere::color));
    loc = 1;
    m_program->enableAttributeArray(loc);
    glVertexAttribPointer(static_cast<GLuint>(loc), 4,
                          GL_FLOAT, GL_FALSE,
                          stride, offset);
    glVertexAttribDivisor(loc, 1);

    m_transInstanceVBO.release();

    m_transVAO->release();
}

QColor Renderer::bgColor() const
{
    return m_bgColor;
}

void Renderer::setBgColor(const QColor &bgColor)
{
    m_bgColor = bgColor;
}
