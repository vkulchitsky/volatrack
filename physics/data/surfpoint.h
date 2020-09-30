/*!
  30 September, 2020
  SurfPoint represents where a Volatile is located on the surface of a sphere
  */

#ifndef SURFPOINT_H
#define SURFPOINT_H

#include "types.h"

namespace volatrack {

class SurfPoint
{
public:

    /**
     * @brief Constructor.
     * @param rect - Cartesian rep of constructed SurfPoint
     */
    SurfPoint(const vec3 &rect);

    /**
     * @brief Constructor.
     * @param x coordinate of Cartesian rep
     * @param y coordinate of Cartesian rep
     * @param z coordinate of Cartesian rep
     */
    SurfPoint(real x, real y, real z);

    /**
     * @brief getter for Cartesian representation
     * @return stored Cartesian rep
     */
    vec3 rect() const;

    /**
     * @brief settter for Cartesian representation
     * @param Cartesian rep being set
     */
    void setRect(const vec3 &rect);

    /**
     * @brief settter for Cartesian representation
     * @param x coordinate of Cartesian rep being set
     * @param y coordinate of Cartesian rep being set
     * @param z coordinate of Cartesian rep being set
     */
    void setRect(real x, real y, real z);

    /**
     * @brief normalizes Cartesian rep to allow a proper SurfPoint
     */
    void normalize();

private:

    // rectangular coordinates, requires one constraint:
    // x * x + y * y + z * z = 1
    // x, y, and z are relative coordinates to spheres[isphere].R
    vec3 m_rect;
};

}

#endif // SURFPOINT_H
