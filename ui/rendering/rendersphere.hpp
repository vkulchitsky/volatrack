#ifndef RENDERSPHERE_H
#define RENDERSPHERE_H

#include <QVector4D>
#include <QMatrix4x4>

class RenderSphere
{
public:
    RenderSphere(const QMatrix4x4& model = {},
                 const QVector4D& color = {0.0, 0.5, 0.5, 1.0})
        : model(model)
        , color(color)
    {}

    //!
    //! \brief model is model matrix(translate, scale, rotate)
    //!
    QMatrix4x4 model;
    //!
    //! \brief color is object color
    //!
    QVector4D color;
};

#endif // RENDERSPHERE_H
