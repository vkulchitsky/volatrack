#ifndef VOLATILE_H
#define VOLATILE_H

#include "types.h"
#include "surfpoint.h"

namespace volatrack {

struct Volatile
{
    Volatile(index i, real x, real y, real z);

    index isphere;
    SurfPoint loc; // location of volatile within surface of sphere

    flagger flags;
};

}

#endif // VOLATILE_H
