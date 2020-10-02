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

/*!
 * \brief Material of a sphere - expected to be lunar regolith
 */
struct Material
{
    Material()
        : rho(0)
        , G(0)
        , nu(0)
        , gamma(0)
        , CR0(0)
        , vR0(0)
        , alpha_t(0)
        , mu(0)
        , rMu{0}
        , rNu{0}
        , rK{0}
        , rTh{0}
        , visc{0}
        , viscg{0}
        , name("nothing")
    {

    }

//    real getRayleighCoef();

    real rho;        //!< density, kg/m^3
    real G;          //!< shear modulus, Pa
    real nu;         //!< poisson coef., 1
    real gamma;      //!< surface energy, J/m^2
    real CR0;        //!< standard restitution, 1
    real vR0;        //!< standard impact velocity, m/s
    real alpha_t;    //!< tangent elastic reduction, 1
    real mu;         //!< friction coefficient
    real rMu;        //!< rolling dry friction coef.
    real rNu;        //!< rolling visc. friction coef.
    real rK;         //!< rolling dry torque growth factor
    real rTh;        //!< rolling visc. torque growth factor
    real visc;       //!< viscosity coefficient for tangential force
    real viscg;      //!< viscosity growth factor

    std::string name;    //!< material name
};

const Material lunarRegolith;

// ???

}

#endif // TYPES_H
