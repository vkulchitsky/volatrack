#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "surfpoint.hpp"

namespace volatrack
{

struct Contact
{
    Contact(Index i1, SurfPoint pt1, Index i2, SurfPoint pt2);

    Index iFirst;
    SurfPoint ptFirst;
    Index iSecond;
    SurfPoint ptSecond;
};

using Contacts = std::vector<Contact>;

}

#endif // CONTACT_HPP
