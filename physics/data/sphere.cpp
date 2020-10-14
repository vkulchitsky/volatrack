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

    // velocity
    QJsonArray velArr = {v.x(), v.y(), v.z()};
    res.insert("velocity", posArr);

    // radius and temperature
    res.insert("radius", R);
    res.insert("temperature", T);

    // material
    res.insert("material", material.saveToJson());

    return res;
}

void Sphere::loadFromJson(const QJsonObject &jo)
{
    auto posArr = jo["position"].toArray();
    c.setX(posArr[0].toDouble());
    c.setY(posArr[1].toDouble());
    c.setZ(posArr[2].toDouble());

    auto velArr = jo["velocity"].toArray();
    v.setX(velArr[0].toDouble());
    v.setY(velArr[1].toDouble());
    v.setZ(velArr[2].toDouble());

    R = jo["radius"].toDouble();
    T = jo["temperature"].toDouble();

    material.loadFromJson(jo["material"].toObject());
}
