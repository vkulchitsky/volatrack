#ifndef RENDERER_H
#define RENDERER_H

#include "physics/data/data.hpp"

#include <QOpenGLWidget>

namespace Ui {
class Renderer;
}

class Renderer : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Renderer(QWidget *parent = nullptr);
    ~Renderer();

    void draw(const volatrack::Data& data);

private:
    Ui::Renderer *ui;
};

#endif // RENDERER_H
