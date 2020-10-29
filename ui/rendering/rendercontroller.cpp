#include "rendercontroller.hpp"

using namespace volatrack;

RenderController::RenderController()
{

}

QVector<RenderSphere> RenderController::spheresFromData(const Data &data)
{
    QVector<RenderSphere> res;

    QVector4D sphereColor(1, 0, 0, 0.5);
    QVector4D volatileColor(0, 1, 0, 1);

    const real volDotScale = 0.05;

    for (auto& sph : data.spheres())
    {
        RenderSphere rs;

        // make rs like sph

        rs.color = sphereColor;

        rs.model.setToIdentity();
        rs.model.translate(sph.c);
        rs.model.scale(sph.R);

        res.push_back(rs);
    }

    for (auto& vol : data.volatiles())
    {
        RenderSphere rs;

        rs.color = volatileColor;

        rs.model.setToIdentity();
        rs.model.translate(vol.absolutePosition(data.spheres()));
        rs.model.scale(volDotScale);

        res.push_back(rs);
    }

    return res;
}
