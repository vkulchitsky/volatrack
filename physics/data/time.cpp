#include "time.hpp"

#include <QJsonObject>

using namespace volatrack;

Time::Time() : t(0), dt(1e-5), dtSave(0.01)
{

}

QJsonObject Time::saveToJson() const
{
    QJsonObject res;

    res.insert("current time", t);
    res.insert("time step", dt);
    res.insert("save time step", dtSave);

    return res;
}

void Time::loadFromJson(const QJsonObject &jo) const
{
    //
}
