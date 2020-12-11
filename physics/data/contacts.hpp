/*!
    Structure that carries information for a contact
    @file contacts.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 11/25/2020
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "surfpoint.hpp"
#include "data.hpp"

namespace volatrack
{

struct Contact
{
    Contact(Index i1, SurfPoint pt1, Index i2, SurfPoint pt2, real delta = 0);
    SurfPoint pointOf(Index index);
    real csArea(const Data& data);

    Index i;
    SurfPoint spi;
    Index j;
    SurfPoint spj;
    real delta;
};

using Contacts = std::vector<Contact>;

}

#endif // CONTACT_HPP
