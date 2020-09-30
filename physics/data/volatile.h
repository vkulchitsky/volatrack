#ifndef VOLATILE_H
#define VOLATILE_H

#include "types.h"
#include "surfpoint.h"

namespace volatrack {

struct Volatile
{
    /**
     * @brief Constructor.
     * @param i - index of sphere to be set
     * @param x coordinate of relative location to be set
     * @param y coordinate of relative location to be set
     * @param z coordinate of relative location to be set
     */
    Volatile(index i, real x, real y, real z);

    index isphere; //!< index of regolith sphere
    SurfPoint loc; //!< location of volatile within surface of sphere

    flagger flags; //!< flags (e.g. type of molecule)
};

}

#endif // VOLATILE_H
