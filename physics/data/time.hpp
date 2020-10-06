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
class Time : CanIO
{
public:

    /*!
     * \brief default constructor
     */
    Time();

    /*!
     * \brief save to json format
     * \returnjson object in Qt form representing the time
     */
    QJsonObject saveToJson() override;

    /*!
     * \brief load from json format
     * \param json object in Qt form representing the time
     */
    void loadFromJson(const QJsonObject &jo) override;

    real t; //!< current time
};

}

#endif // TIME_HPP
