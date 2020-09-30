#include "sphere.h"
using namespace volatrack;

Sphere::Sphere(real x, real y, real z, real R)
    : c(x, y, z)
    , R(R)
    , T(waterFreeze)
    , material(lunarRegolith)
{}

Sphere::Sphere(vec3 pos, real R)
    : c(pos)
    , R(R)
    , T(waterFreeze)
    , material(lunarRegolith)
{}
