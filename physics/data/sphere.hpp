/*!
  Sphere/spheres data structure
  @file sphere.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/02/2020
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"

namespace volatrack
{

/*!
 * \brief a sphere approximates a soil particle on the moon
 */
struct Sphere
{
    Sphere(real x, real y, real z, real R);

    Sphere(vec3 pos, real R);

    vec3 c; //!< position
    real R; //!< radius
    real T; //!< temperature in Kelvin
    Material material;
};

///*!
// * \brief inheriting sphere vector for flexibility
// */
//class Spheres : public std::vector<Sphere>
//{
//public:
//    /*!
//     * \brief push sphere to spheres
//     * \param x coordinate of center
//     * \param y coordinate of center
//     * \param z coordinate of center
//     * \param R - radius
//     */
//    void pushSphere(real x, real y, real z, real R);
//    void pushSphere(const vec3& pos, real R);
//};

using Spheres = std::vector<Sphere>;

//using Spheres = std::vector<Sphere>
//Spheres data;
//data.push_back(Sphere{1, 2, 3, 4});
//data.push_back(Sphere{vec3{0, 0, 0}, 1});
}

#endif // SPHERE_H
