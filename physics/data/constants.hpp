/*!
    Constants are stored here
    @file constants.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/19/2020
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "types.hpp"

namespace volatrack
{

const real waterFreeze = 273.15; //!< water freezing temperature

// will be adjusted to the correct value!
const real tau = 1e-5; //!< standard volatile movement time

// will be adjusted to the correct value!
const real E0 = 2e-20; //!< standard energy for volatile

const real kB = 1.38e-23; //!< Boltzman's constant

// will be adjusted to the correct value!
const real d0Rel = 1.0; //!< maximum volatile travel relative to sphere

const real PI = 3.14159265358979323846264;

}

#endif // CONSTANTS_HPP
