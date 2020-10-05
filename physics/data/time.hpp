/*!
    Time tracker
    @file time.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/05/2020
*/

#ifndef TIME_HPP
#define TIME_HPP

#include "types.hpp"

namespace volatrack
{

/*!
 * \brief Time tracker - includes current time and may include additional info
 */
class Time
{
public:

    /*!
     * \brief default constructor
     */
    Time();

    real t; //!< current time
};

}

#endif // TIME_HPP
