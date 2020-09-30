/*!


  */

#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <cmath>

namespace volatrack
{

using real = double;
using index = unsigned int;
using flagger = unsigned int;

const real waterFreeze = 273.15; // water freezing temperature

struct vec3
{
    vec3(real x, real y, real z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }
    vec3 operator-(const vec3& other)
    {
        return {x - other.x, y - other.y, z - other.z};
    }
    bool operator==(const vec3& other)
    {
        return (x == other.x && y == other.y && z == other.z);
    }
    void operator=(const vec3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    vec3 operator*(real k)
    {
        x *= k;
        y *= k;
        z *= k;
    }
    vec3 operator/(real k)
    {
        x /= k;
        y /= k;
        z /= k;
    }

    real operator*(const vec3& other)
    {
        return x * other.x + y * other.y + z * other.z;
    }
    vec3 operator%(const vec3& other)
    {
        real X = y * other.z - z * other.y;
        real Y = z * other.x - x * other.z;
        real Z = x * other.y - y * other.x;

        return {X, Y, Z};
    }

    real length2() {return x * x + y * y + z * z;}
    real length() {return std::sqrt(length2());}

    real x;
    real y;
    real z;
};

struct quat
{
    quat(real x, real y, real z, real w) : x(x), y(y), z(z), w(w) {}

    real x;
    real y;
    real z;
    real w;
};

struct Material
{
    // properties: density? shear modulus? etc.
};

const Material lunarRegolith;

// ???

}

#endif // TYPES_H
