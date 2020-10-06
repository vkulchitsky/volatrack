#include "volatile.hpp"

#include <QJsonObject>
#include <QJsonArray>

using namespace volatrack;

Volatile::Volatile(Index i, real x, real y, real z)
    : isphere(i)
    , loc(x, y, z)
    , flags(0)
{}

vec3 Volatile::absolutePosition(const Spheres &spheres) const
{
    const Sphere& sphere = spheres[isphere];

    return sphere.c + loc.rect() * sphere.R;
}

QJsonObject Volatile::saveToJson() const
{
    QJsonObject res;

    // sphere index
    res.insert("isphere", static_cast<int>(isphere));

    // surface location
    QJsonArray surfLocArr = {loc.rect().x(), loc.rect().y(),
                            loc.rect().z()};
    res.insert("surface location", surfLocArr);

    // flags
    res.insert("flags", static_cast<int>(flags));

    return res;
}

void Volatile::loadFromJson(const QJsonObject &jo) const
{
    //
}
