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

//struct vec3
//{
//    vec3(real x, real y, real z) : x(x), y(y), z(z) {}

//    vec3 operator+(const vec3& other)
//    {
//        return {x + other.x, y + other.y, z + other.z};
//    }
//    vec3 operator-(const vec3& other)
//    {
//        return {x - other.x, y - other.y, z - other.z};
//    }
//    bool operator==(const vec3& other)
//    {
//        return (x == other.x && y == other.y && z == other.z);
//    }
//    void operator=(const vec3& other)
//    {
//        x = other.x;
//        y = other.y;
//        z = other.z;
//    }

//    vec3 operator*(real k)
//    {
//        return {x * k, y * k, z * k};
//    }
//    vec3 operator/(real k)
//    {
//        return {x / k, y / k, z/ k};
//    }

//    real operator*(const vec3& other)
//    {
//        return x * other.x + y * other.y + z * other.z;
//    }
//    vec3 operator%(const vec3& other)
//    {
//        real X = y * other.z - z * other.y;
//        real Y = z * other.x - x * other.z;
//        real Z = x * other.y - y * other.x;

//        return {X, Y, Z};
//    }

//    real length2() {return x * x + y * y + z * z;}
//    real length() {return std::sqrt(length2());}

//    real x;
//    real y;
//    real z;
//};

using vec3 = QVector3D;

struct CanIO
{
    virtual QJsonObject saveToJson() = 0;
    virtual void loadFromJson(const QJsonObject& jo) = 0;
};

// ???

}

#endif // TYPES_H
