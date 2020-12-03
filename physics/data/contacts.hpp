/*!
    Structure that carries information for a contact
    @file contacts.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 11/25/2020
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "surfpoint.hpp"

namespace volatrack
{

struct Contact
{
    Contact(Index i1, SurfPoint pt1, Index i2, SurfPoint pt2);
    SurfPoint pointOf(Index index);

    Index i;
    SurfPoint spi;
    Index j;
    SurfPoint spj;
};

using Contacts = std::vector<Contact>;

}

#endif // CONTACT_HPP
