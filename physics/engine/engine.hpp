/*!
    The main physical engine
    @file engine.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/05/2020
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "physics/data/data.hpp"
#include "physics/data/contacts.hpp"

namespace volatrack {

/*!
 * \brief The physical engine - main process
 */
class Engine
{
public:
    /*!
     * \brief default constructor
     */
    Engine();

    /*!
     * \brief constructor with data - may or may not be necessary
     * \param data
     */
    Engine(const Data &data);

    /*!
     * \brief process for random walk portion that alters data accordingly
     * \param data to be altered
     */
    void randomWalkProcess(Data& data);

    /*!
     * \brief process for jumping from sphere to sphere that alters data
     * accordingly
     * \param data to be altered
     */
    void jumpingProcess(Data& data);

    /*!
     * \brief initital steps for starting simulation
     * \param data
     */
    void init(const Data& data);

    /*!
     * \brief if called, data is saved to a file
     * \param data
     * \return whether data is in need of saving
     */
    bool needsSaving(const Data& data);

    /*!
     * \brief if called, engine checks for sphere-to-sphere jumping
     * \param data
     * \return whether the engine must check for jumping
     */
    bool needsJumpCheck(const Data& data);

    /*!
     * \brief whether two spheres are near each other
     * \param data
     * \param i - first index
     * \param j - second index
     * \param dR - allowed distance
     * \return whether surfaces are less than dR away
     */
    static bool areNear(const Data& data, Index i, Index j, real dR = 0);

    /*!
     * \brief contact detection
     * \param data
     * \param dR - how close they have to be
     * \return list of all contacts
     */
    Contacts getContacts(const Data& data, real dR = 0);

    /*!
     * \brief use random double generator that is given
     * \param generator
     */
    void passGen(const std::shared_ptr<std::default_random_engine> &gen);

private:

    real stdrdSphDist(Index isphere, const Data &data);

    real m_lastSaveTime;
    real m_lastJumpCheckTime;
    real m_timeVolCoeff;
    std::shared_ptr<std::default_random_engine> m_gen;
};

}

#endif // ENGINE_H
