#ifndef SPHERE_H
#define SPHERE_H

#include "types.h"

namespace volatrack
{

struct Sphere
{
    Sphere(real x, real y, real z, real R);

    Sphere(vec3 pos, real R);

    vec3 c; //!< position
    real R; //!< radius
    real T; //!< temperature in Kelvin
    Material material;
};

}

#endif // SPHERE_H
