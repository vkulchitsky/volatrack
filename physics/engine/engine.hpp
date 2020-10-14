/*!
    The main physical engine
    @file engine.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/05/2020
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "physics/data/data.hpp"

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
     * \brief process that alters data accordingly
     * \param data to be altered
     */
    void process(Data& data);

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
     * \brief whether two spheres are near each other
     * \param data
     * \param i - first index
     * \param j - second index
     * \param dR - allowed distance
     * \return whether surfaces are less than dR away
     */
    static bool areNear(const Data& data, Index i, Index j, real dR = 0);

    Pairs getContacts(const Data& data, real dR = 0);

private:
    real m_lastSaveTime;
};

}

#endif // ENGINE_H
