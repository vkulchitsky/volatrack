#ifndef VOLATILE_H
#define VOLATILE_H

#include "types.h"

namespace volatrack {

struct Volatile
{
    Volatile(index i, real x, real y, real z)
        : isphere(i)
        , loc(x, y, z)
        , flags(0)
    {}

    index isphere;
    SurfaceLocation loc; // location of volatile within surface of sphere

    flagger flags;
};

}

#endif // VOLATILE_H
