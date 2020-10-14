/*!
  Sphere/spheres data structure
  @file sphere.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/02/2020
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "material.hpp"

namespace volatrack
{

/*!
 * \brief a sphere approximates a soil particle on the moon
 */
struct Sphere : CanIO
{
    /*!
     * \brief constructor from coordinates and radius
     * \param x coordinate
     * \param y coordinate
     * \param z coordinate
     * \param R - radius
     */
    Sphere(real x, real y, real z, real R);

    /*!
     * \brief constructor from position and radius
     * \param pos - position of sphere
     * \param R - radius
     */
    Sphere(vec3 pos, real R);

    /*!
     * \brief save to json format
     * \return json object in Qt form representing the sphere
     */
    QJsonObject saveToJson() const override;

    /*!
     * \brief load from json format
     * \param json object in Qt form representing the sphere
     */
    void loadFromJson(const QJsonObject &jo) override;

    vec3 c; //!< position
    real R; //!< radius
    real T; //!< temperature in Kelvin
    Material material;
};

using Spheres = std::vector<Sphere>; //!< defining Spheres as Sphere vector

}

#endif // SPHERE_H
