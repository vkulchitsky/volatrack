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
#include <QMatrix3x3>
#include <QString>
#include <QJsonObject>

namespace volatrack
{

using real = double;
using Index = unsigned int;
using Flagger = unsigned int;

using vec3 = QVector3D;
using quat = QVector4D;

struct mat3
{
    QVector3D leftColumn;
    QVector3D middleColumn;
    QVector3D rightColumn;

    QVector3D topRow()
    {
        return {leftColumn.x(), middleColumn.x(), rightColumn.x()};
    }

    QVector3D middleRow()
    {
        return {leftColumn.y(), middleColumn.y(), rightColumn.y()};
    }

    QVector3D bottomRow()
    {
        return {leftColumn.z(), middleColumn.z(), rightColumn.z()};
    }

    mat3 operator+(const mat3& other)
    {
        mat3 res;

        res.leftColumn = leftColumn + other.leftColumn;
        res.middleColumn = middleColumn + other.middleColumn;
        res.rightColumn = rightColumn + other.rightColumn;

        return res;
    }

    mat3 operator-(const mat3& other)
    {
        mat3 res;

        res.leftColumn = leftColumn - other.leftColumn;
        res.middleColumn = middleColumn - other.middleColumn;
        res.rightColumn = rightColumn - other.rightColumn;

        return res;
    }

    vec3 operator*(const vec3& original)
    {
        return
        {
            QVector3D::dotProduct(topRow(), original),
            QVector3D::dotProduct(middleRow(), original),
            QVector3D::dotProduct(bottomRow(), original)
        };
    }

    mat3 operator*(const mat3& other)
    {
        return
        {
            *this * other.leftColumn,
            *this * other.middleColumn,
            *this * other.rightColumn
        };
    }
};

using Pairs = std::vector<std::pair<Index, Index>>;

struct CanIO
{
    virtual QJsonObject saveToJson() const = 0;
    virtual void loadFromJson(const QJsonObject& jo) = 0;
};

}

#endif // TYPES_H
