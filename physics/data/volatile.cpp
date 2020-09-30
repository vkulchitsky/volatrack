#include "volatile.h"

using namespace volatrack;

Volatile::Volatile(index i, real x, real y, real z)
    : isphere(i)
    , loc(x, y, z)
    , flags(0)
{}
