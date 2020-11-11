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

#include <memory>
#include <random>

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
    QJsonObject saveToJson() const override;

    /*!
     * \brief load from json format
     * \param json object in Qt form representing the data
     */
    void loadFromJson(const QJsonObject &jo) override;

    /*!
     * \brief setter for spheres array with move semantics
     * \param spheres to set
     */
    void setSpheresArray(const Spheres&& spheres);

    /*!
     * \brief setter for volatiles array with move semantics
     * \param volatiles to set
     */
    void setVolatilesArray(const Volatiles&& volatiles);

    /*!
     * \brief load each sphere uniformly with six volatiles
     */
    void loadSpheresEvenly();

    /*!
     * \brief load each sphere with volatiles randomly distributed
     * \param number of volatiles on each sphere
     * \param whether each sphere has the same number of volatiles, or it's
     * also random
     */
    void loadSpheresRandomly(Size volsPerSphere, bool constVols = false);

    /*!
     * \brief simple data sample for testing
     * \return the data sample
     */
    static Data quickData();

    static Data diffusionData();

    /*!
     * \brief use random double generator that is given
     * \param generator
     */
    void passGen(const std::shared_ptr<std::default_random_engine> &gen);

    Time time;    

private:
    void loadSphereEvenly(Index isphere);
    void loadSphereRandomly(Index isphere, Size number);
    void addRandomVolatile(Index isphere);

    Spheres m_spheres;
    Volatiles m_volatiles;
    std::shared_ptr<std::default_random_engine> m_gen;
};

}

#endif // DATA_H
