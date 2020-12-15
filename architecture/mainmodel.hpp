/*!
    Primary architecture for Volatrack
    @file mainmodel.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/19/2020
*/

#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "physics/data/sphere.hpp"
#include "physics/data/volatile.hpp"
#include "physics/data/data.hpp"
#include "io/projectcontroller.hpp"
#include "io/sphereimporter.hpp"

#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>

namespace volatrack
{

/*!
 * \brief The main model for Volatrack
 */
class MainModel
{
public:

    /*!
     * \brief Default constructor
     */
    MainModel();

    /*!
     * \brief one second test run with hardcoded data
     */
    void simpleTestRun();

    /*!
     * \brief one second test run with dispersion model
     */
    void diffusionTestRun();

    /*!
     * \brief first test of volatile jumpings with two spheres
     */
    void twoSphereJumping();

    /*!
     * \brief run simulation from json file
     * \param file to run
     * \param length of simulation
     * \param project name
     * \param target directory
     */
    void runFromJson(const QString& runFile, real simTime = 1.0,
                     const QString& projName = "JsonImport",
                     const QString& targetDir = QDir::homePath());

private:

    void commonLoop(const QString& projName, const QString& targetDir
                    = QDir::homePath(), real simTime = 1.0);
    void scanData();

    Data m_data;
    std::shared_ptr<std::default_random_engine> m_gen;
};

}

#endif // MAINMODEL_H
