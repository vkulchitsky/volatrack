#include "contacts.hpp"

using namespace volatrack;

Contact::Contact(volatrack::Index i1, SurfPoint pt1,
                            volatrack::Index i2, SurfPoint pt2)
    : i(i1), spi(pt1), j(i2), spj(pt2)
{}

SurfPoint Contact::pointOf(Index index)
{
    if (index == i) return spi;
    if (index == j) return spj;

    throw std::runtime_error("Unknown index used in contact.");
}
