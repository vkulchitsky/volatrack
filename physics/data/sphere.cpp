#include "sphere.hpp"
using namespace volatrack;

Sphere::Sphere(real x, real y, real z, real R)
    : c(x, y, z)
    , R(R)
    , T(waterFreeze)
    , material()
{}

Sphere::Sphere(vec3 pos, real R)
    : c(pos)
    , R(R)
    , T(waterFreeze)
    , material(lunarRegolith)
{}

//void Spheres::pushSphere(real x, real y, real z, real R)
//{
//    Sphere sph(x, y, z, R);
//    push_back(sph);
//}

//void Spheres::pushSphere(const vec3 &pos, real R)
//{
//    Sphere sph(pos, R);
//    push_back(sph);
//}
