#include "sphere.hpp"

#include <QJsonArray>

using namespace volatrack;

Sphere::Sphere(real x, real y, real z, real R)
    : c(x, y, z)
    , R(R)
    , T(waterFreeze)
    , material()
{}

Sphere::Sphere(vec3 pos, real R)
    : c(pos)
    , R(R)
    , T(waterFreeze)
    , material(lunarRegolith)
{}

QJsonObject Sphere::saveToJson() const
{
    QJsonObject res;

    // position
    QJsonArray posArr = {c.x(), c.y(), c.z()};
    res.insert("position", posArr);

    // radius and temperature
    res.insert("radius", R);
    res.insert("temperature", T);

    // material
    res.insert("material", material.saveToJson());

    return res;
}

void Sphere::loadFromJson(const QJsonObject &jo) const
{
    //
}
