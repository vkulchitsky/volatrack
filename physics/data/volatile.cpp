#include "volatile.hpp"

using namespace volatrack;

Volatile::Volatile(Index i, real x, real y, real z)
    : isphere(i)
    , loc(x, y, z)
    , flags(0)
{}

vec3 Volatile::absolutePosition(const Spheres &spheres)
{
    const Sphere& sphere = spheres[isphere];

    return sphere.c + loc.rect() * sphere.R;
}

void Volatiles::pushVolatile(Index i, real x, real y, real z)
{
    Volatile vol(i, x, y, z);
    push_back(vol);
}
