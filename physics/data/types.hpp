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
#include <QVector4D>
#include <QString>
#include <QJsonObject>

namespace volatrack
{

using real = double;
using Index = unsigned int;
using Size = unsigned long;
using Flagger = unsigned int;

using vec3 = QVector3D;
using vec4 = QVector4D;

struct CanIO
{
    virtual QJsonObject saveToJson() const = 0;
    virtual void loadFromJson(const QJsonObject& jo) = 0;
};

}

#endif // TYPES_H
