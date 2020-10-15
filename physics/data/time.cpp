#include "time.hpp"
#include "defs.hpp"

#include <QJsonObject>

using namespace volatrack;

Time::Time() : t(0), dt(1e-5), dtSave(0.01)
{

}

QJsonObject Time::saveToJson() const
{
    QJsonObject res;

    res.insert(TIME_CURRENT, t);
    res.insert(TIME_STEP, dt);
    res.insert(TIME_SAVE_STEP, dtSave);

    return res;
}

void Time::loadFromJson(const QJsonObject &jo)
{
    t = jo[TIME_CURRENT].toDouble();
    dt = jo[TIME_STEP].toDouble();
    dtSave = jo[TIME_SAVE_STEP].toDouble();
}
