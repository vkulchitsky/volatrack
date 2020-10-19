/*!
  Data structure for point on surface of sphere
  @file surfpoint.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/02/2020
*/

#ifndef SURFPOINT_H
#define SURFPOINT_H

#include "types.hpp"

namespace volatrack {

/*!
 * \brief The SurfPoint class
 * rectangular coordinates, requires one constraint:
    x * x + y * y + z * z = 1
    x, y, and z are relative coordinates to spheres[isphere].R
 */
class SurfPoint
{
public:

    /*!
     * \brief Constructor.
     * \param rect - Cartesian rep of constructed SurfPoint
     */
    SurfPoint(const vec3 &rect);

    /*!
     * \brief Constructor.
     * \param x coordinate of Cartesian rep
     * \param y coordinate of Cartesian rep
     * \param z coordinate of Cartesian rep
     */
    SurfPoint(real x, real y, real z);

    /*!
     * \brief getter for Cartesian representation
     * @return stored Cartesian rep
     */
    vec3 rect() const;

    /*!
     * \brief settter for Cartesian representation
     * \param Cartesian rep being set
     */
    void setRect(const vec3 &rect);

    /*!
     * \brief settter for Cartesian representation
     * \param x coordinate of Cartesian rep being set
     * \param y coordinate of Cartesian rep being set
     * \param z coordinate of Cartesian rep being set
     */
    void setRect(real x, real y, real z);

    /*!
     * \brief normalizes Cartesian rep to allow a proper SurfPoint
     */
    void normalize();

    /*!
     * \brief move location on sphere by a small amount into given direction
     * \param d - how much to move
     * \param alpha - in what direction to move
     */
    void moveBy(real d, real alpha);

private:

    mat3 frame();

    // rectangular coordinates, requires one constraint:
    // x * x + y * y + z * z = 1
    // x, y, and z are relative coordinates to spheres[isphere].R
    vec3 m_rect;
};

}

#endif // SURFPOINT_H
