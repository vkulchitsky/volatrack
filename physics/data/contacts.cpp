#include "contacts.hpp"

using namespace volatrack;

Contact::Contact(volatrack::Index i1, SurfPoint pt1,
                            volatrack::Index i2, SurfPoint pt2)
    : iFirst(i1), ptFirst(pt1), iSecond(i2), ptSecond(pt2)
{}
