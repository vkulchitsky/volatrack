/*!
  Predefined types
  @file types.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/02/2020
*/

#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <cmath>

#include <QVector3D>
#include <QString>
#include <QJsonObject>

namespace volatrack
{

using real = double;
using Index = unsigned int;
using Flagger = unsigned int;

const real waterFreeze = 273.15; // water freezing temperature

using vec3 = QVector3D;

struct CanIO
{
    virtual QJsonObject saveToJson() const = 0;
    virtual void loadFromJson(const QJsonObject& jo) const = 0;
};

}

#endif // TYPES_H
