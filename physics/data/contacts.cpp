#include "contacts.hpp"

using namespace volatrack;

Contact::Contact(volatrack::Index i1, SurfPoint pt1,
                            volatrack::Index i2, SurfPoint pt2, real delta)
    : i(i1), spi(pt1), j(i2), spj(pt2), delta(delta)
{}

SurfPoint Contact::pointOf(Index index)
{
    // match index to contact point
    if (index == i) return spi;
    if (index == j) return spj;

    // if it doesn't match, throw an error
    throw std::runtime_error("Unknown index used in contact.");
}

real Contact::csArea(const Data &data)
{
    // get both radii
    auto Ri = data.spheres()[i].R;
    auto Rj = data.spheres()[j].R;

    // composite radius (harmonic mean of both radii)
    auto R = 2 * Ri * Rj / (Ri + Rj);

    // approximation to O(delta)
    return cst::PI * R * delta;
}
