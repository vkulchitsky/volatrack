#ifndef SURFPOINT_H
#define SURFPOINT_H

#include "types.h"

namespace volatrack {



class SurfPoint
{
public:
    SurfPoint(const vec3 &rect);
    SurfPoint(real x, real y, real z);

    vec3 rect() const;
    void setRect(const vec3 &rect);
    void setRect(real x, real y, real z);

private:
    vec3 m_rect;
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





    /* Alternative choice - ABSOLUTE LATITUDE AND ABSOLUTE LONGITUDE */

    // Two meridians (prime meridian and half of equator)
    // Each parameter is distance to each meridian
};

}

#endif // SURFPOINT_H
