/*!


  */

#ifndef TYPE_H
#define TYPE_H

#include <vector>

namespace volatrack
{

using real = double;
using index = unsigned int;
using flagger = unsigned int;

const real waterFreeze = 273.15; // water freezing temperature

struct vec3
{
    vec3(real x, real y, real z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& other);
    vec3 operator-(const vec3& other);
    bool operator==(const vec3& other);
    void operator=(const vec3& other);

    real operator*(const vec3& other);
    vec3 operator%(const vec3& other);

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

struct SurfaceLocation
{
    SurfaceLocation(real x, real y, real z) : rect(x, y, z) {}

    quat getQuat();

    vec3 rect; // rectangular coordinates, requires one constraint:
    // x * x + y * y + z * z = 1
    // x, y, and z are relative coordinates to spheres[isphere].R

    // The problem is that the change in location cannot be represented
    // like this. Only the location itself.



    /* Alternative choice - QUATERNION */

    // Has two constraints - normalization and one of the Euler angles = 0
    // It's nice to add (same type for location and change for location)

    // Normalizing is easy, but setting the Euler angle to zero may be
    // difficult or expensive



    /* Alternative choice - LATITUDE AND ABSOLUTE LONGITUDE */

    // Latitude works the same as regular latitude

    // Longitude is ABSOLUTE, so instead of asimuthal angle we measure arc
    // length, or, with the global analogy, we measure how far east of the
    // prime meridian we are

    // At the Poles it doesn't matter where the Prime Meridian is, because
    // this arc length is always zero



    /* Alternative choice - ABSOLUTE LATITUDE AND ABSOLUTE LONGITUDE */

    // Two meridians (prime meridian and half of equator)
    // Each parameter is distance to each meridian
};

struct Material
{
    // properties: density? shear modulus? etc.
};

const Material mat; // ???

}

#endif // TYPES_H
