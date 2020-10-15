#include "sphere.hpp"
#include "defs.hpp"

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
    res.insert(SPHERE_POSITION, posArr);

    // orientation
    QJsonArray oriArr = {q.x(), q.y(), q.z(), q.w()};
    res.insert(SPHERE_ROTATION, oriArr);

    // velocity
    QJsonArray velArr = {v.x(), v.y(), v.z()};
    res.insert(SPHERE_VELOCITY, posArr);

    // radius and temperature
    res.insert(SPHERE_RADIUS, R);
    res.insert(SPHERE_TEMPERATURE, T);

    // material
    res.insert(SPHERE_MATERIAL, material.saveToJson());

    return res;
}

void Sphere::loadFromJson(const QJsonObject &jo)
{
    auto posArr = jo[SPHERE_POSITION].toArray();
    c.setX(posArr[0].toDouble());
    c.setY(posArr[1].toDouble());
    c.setZ(posArr[2].toDouble());

    auto oriArr = jo[SPHERE_ROTATION].toArray();
    q.setX(oriArr[0].toDouble());
    q.setY(oriArr[1].toDouble());
    q.setZ(oriArr[2].toDouble());
    q.setW(oriArr[3].toDouble());

    auto velArr = jo[SPHERE_VELOCITY].toArray();
    v.setX(velArr[0].toDouble());
    v.setY(velArr[1].toDouble());
    v.setZ(velArr[2].toDouble());

    R = jo[SPHERE_RADIUS].toDouble();
    T = jo[SPHERE_TEMPERATURE].toDouble();

    material.loadFromJson(jo[SPHERE_MATERIAL].toObject());
}
