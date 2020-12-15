#include "volatile.hpp"
#include "defs.hpp"

#include <QJsonObject>
#include <QJsonArray>

using namespace volatrack;

Volatile::Volatile(Index i, real x, real y, real z)
    : isphere(i)
    , loc(x, y, z)
    , igroup(0)
    , flags(0)
{
    loc.normalize();
}

vec3 Volatile::absolutePosition(const Spheres &spheres) const
{
    const Sphere& sphere = spheres[isphere];

    auto res = sphere.c + loc.rect() * sphere.R;

    return res;
}

QJsonObject Volatile::saveToJson() const
{
    QJsonObject res;

    // sphere index
    res.insert(VOL_SPH_INDEX, static_cast<int>(isphere));

    // surface location
    QJsonArray surfLocArr = {loc.rect().x(), loc.rect().y(),
                            loc.rect().z()};
    res.insert(VOL_SURLOC, surfLocArr);

    // group
    res.insert(VOL_GROUP, static_cast<int>(igroup));

    // flags
    res.insert(VOL_FLAGS, static_cast<int>(flags));

    return res;
}

void Volatile::loadFromJson(const QJsonObject &jo)
{
    isphere = static_cast<Index>(jo[VOL_SPH_INDEX].toInt());

    auto surfLocArr = jo[VOL_SURLOC].toArray();
    auto rect = loc.rect();

    rect.setX(surfLocArr[0].toDouble());
    rect.setY(surfLocArr[1].toDouble());
    rect.setZ(surfLocArr[2].toDouble());

    loc.setRect(rect);
    igroup = jo[VOL_GROUP].toInt();
    flags = static_cast<Flagger>(jo[VOL_FLAGS].toInt());
}

QJsonObject VolGroup::saveToJson() const
{
    QJsonObject res;

    // color
    QJsonArray colorArr = {color.x(), color.y(), color.z(), color.w()};
    res.insert(GROUP_COLOR, colorArr);

    // name
    res.insert(GROUP_NAME, name);

    return res;
}

void VolGroup::loadFromJson(const QJsonObject &jo)
{
    auto oriArr = jo[GROUP_COLOR].toArray();
    color.setX(oriArr[0].toDouble());
    color.setY(oriArr[1].toDouble());
    color.setZ(oriArr[2].toDouble());
    color.setW(oriArr[3].toDouble());

    name = jo[GROUP_NAME].toString();
}
