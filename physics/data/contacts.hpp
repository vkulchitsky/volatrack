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

/*!
 * \brief Information for a contact
 */
struct Contact
{
    /*!
     * \brief Contact constructor
     * \param i1 - index of first sphere
     * \param pt1 - contact point of first sphere
     * \param i2 - index of second sphere
     * \param pt2 - contact point of second sphere
     * \param delta - intersection margin
     */
    Contact(Index i1, SurfPoint pt1, Index i2, SurfPoint pt2, real delta = 0);

    /*!
     * \brief contact point of sphere from index
     * \param index of sphere
     * \return contact point of the sphere with index above
     */
    SurfPoint pointOf(Index index);

    /*!
     * \brief cross sectional area
     * \param data
     * \return cross sectional area of current contact based on data
     */
    real csArea(const Data& data);

    Index i; //!< index of first sphere
    SurfPoint spi; //!< contact point of first sphere
    Index j; //!< index of second sphere
    SurfPoint spj; //!< contact point of second sphere
    real delta; //!< intersection margin
};

using Contacts = std::vector<Contact>;

}

#endif // CONTACT_HPP
