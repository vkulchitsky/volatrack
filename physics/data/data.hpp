/*!
    Data structure for full data with IO
    @file data.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/05/2020
*/

#ifndef DATA_H
#define DATA_H

#include "volatile.hpp"
#include "time.hpp"

namespace volatrack
{

/*!
 * \brief The Data class stores all data together
 */
class Data : CanIO
{
public:

    /*!
     * \brief default constructor
     */
    Data();

    /*!
     * \brief constructor from spheres and volatiles
     * \param spheres
     * \param vols
     */
    Data(const Spheres&& spheres, const Volatiles&& vols);

    /*!
     * \brief spheres getter
     * \return stored spheres
     */
    Spheres spheres() const;

    /*!
     * \brief volatiles getter
     * \return stored volatiles
     */
    Volatiles volatiles() const;

    /*!
     * \brief time tracker
     * \return time data
     */
    Time time() const;

    /*!
     * \brief push sphere to data
     * \param sphere to be pushed
     */
    void pushSphere(const Sphere& sphere);

    /*!
     * \brief push volatile to data
     * \param volatile to push
     */
    void pushVolatile(const Volatile& vol);

    /*!
     * \brief save to json format
     * \return json object in Qt form representing the data
     */
    QJsonObject saveToJson() override;

    /*!
     * \brief load from json format
     * \param json object in Qt form representing the data
     */
    void loadFromJson(const QJsonObject &jo) override;

private:
    Spheres m_spheres;
    Volatiles m_volatiles;
    Time m_time;
};

}

#endif // DATA_H
