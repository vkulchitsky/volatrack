#include "time.hpp"

#include <QJsonObject>

using namespace volatrack;

Time::Time() : t(0)
{

}

QJsonObject Time::saveToJson()
{
    QJsonObject res;

    res.insert("current time", t);

    return res;
}

void Time::loadFromJson(const QJsonObject &jo)
{
    //
}
