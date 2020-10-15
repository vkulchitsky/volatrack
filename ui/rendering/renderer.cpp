#include "renderer.h"
#include "ui_renderer.h"

using namespace volatrack;

Renderer::Renderer(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::Renderer)
{
    ui->setupUi(this);
}

Renderer::~Renderer()
{
    delete ui;
}

void Renderer::draw(const Data &data)
{
    //
}
