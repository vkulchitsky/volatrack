/*!
  Volatile/volatiles data structure
  @file volatile.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/02/2020
*/

#ifndef VOLATILE_H
#define VOLATILE_H

#include "types.hpp"
#include "surfpoint.hpp"
#include "sphere.hpp"

namespace volatrack {

struct Volatile : CanIO
{
    /*!
     * \brief Constructor.
     * \param i - index of sphere to be set
     * \param x coordinate of relative location to be set
     * \param y coordinate of relative location to be set
     * \param z coordinate of relative location to be set
     */
    Volatile(Index i, real x, real y, real z);

    /*!
     * \brief absolutePosition
     * \param spheres to which volatile points with index
     * \return absolute position, not just relative to sphere
     */
    vec3 absolutePosition(const Spheres& spheres) const;

    QJsonObject saveToJson() override;
    void loadFromJson(const QJsonObject &jo) override;

    Index isphere; //!< index of regolith sphere
    SurfPoint loc; //!< location of volatile within surface of sphere

    Flagger flags; //!< flags (e.g. type of molecule)
};

//! defining Volatiles as Volatile vector
using Volatiles = std::vector<Volatile>;

}

#endif // VOLATILE_H
