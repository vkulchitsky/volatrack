/*!
  Renderer for spheres
  @file renderer.h
  @author Serhii Lytvynenko
  @version 1.0 10/26/2020
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_2_Compatibility>

#include "rendersphere.hpp"
#include "camera.hpp"

class QOpenGLShaderProgram;

class Renderer : public QOpenGLWidget,
        protected QOpenGLFunctions_4_2_Compatibility
{
    Q_OBJECT
public:
    Renderer(QWidget* parent = nullptr);
    ~Renderer();
    //!
    //! \brief setSpheres
    //! \param spheres is input data
    //!
    void setSpheres(const QVector<RenderSphere>& spheres);
    //!
    //! \brief bgColor
    //! \return background color
    //!
    QColor bgColor() const;
    //!
    //! \brief setBgColor
    //! \param bgColor
    //!
    void setBgColor(const QColor &bgColor);

protected:
    //!
    //! \brief initializeGL
    //!
    void initializeGL() override;
    //!
    //! \brief paintGL
    //!
    void paintGL() override;
    //!
    //! \brief resizeGL
    //! \param w is width of the viewport
    //! \param h is height of the viewport
    //!
    void resizeGL(int w, int h) override;
    //!
    //! \brief wheelEvent
    //! \param event
    //!
    void wheelEvent(QWheelEvent *event) override;
    //!
    //! \brief keyPressEvent
    //! \param event
    //!
    void keyPressEvent(QKeyEvent *event) override;
    //!
    //! \brief mousePressEvent
    //! \param event
    //!
    void mousePressEvent(QMouseEvent*event) override;
    //!
    //! \brief mouseMoveEvent
    //! \param event
    //!
    void mouseMoveEvent(QMouseEvent* event) override;
private:
    //!
    //! \brief setupMesh load shape-geometry to device
    //!
    void setupMesh();

    //!
    //! \brief m_program
    //!
    QOpenGLShaderProgram* m_program;
    //!
    //! \brief m_bgColor
    //!
    QColor m_bgColor;
    // OpenGL
    //!
    //! \brief m_opaqueVAO
    //!
    QOpenGLVertexArrayObject* m_opaqueVAO;
    //!
    //! \brief m_transVAO
    //!
    QOpenGLVertexArrayObject* m_transVAO;
    //!
    //! \brief m_spheresVBO
    //!
    QOpenGLBuffer m_spheresVBO;
    //!
    //! \brief m_spheresEBO
    //!
    QOpenGLBuffer m_spheresEBO;
    //!
    //! \brief m_opInstanceVBO
    //!
    QOpenGLBuffer m_opInstanceVBO;
    //!
    //! \brief m_transInstanceVBO
    //!
    QOpenGLBuffer m_transInstanceVBO;
    //!
    //! \brief m_opaqueCount
    //!
    unsigned int m_opaqueCount;
    //!
    //! \brief m_transCount
    //!
    unsigned int m_transCount;
    //!
    //! \brief m_camera
    //!
    Camera m_camera;
    //!
    //! \brief m_lastX cursor x
    //!
    float m_lastX;
    //!
    //! \brief m_lastY cursor y
    //!
    float m_lastY;
};

#endif // RENDERER_H
