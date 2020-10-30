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
#include "physics/engine/engine.hpp"
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
    MainModel();

    void simpleTestRun();
    void runFromJson(const QString& runFile, real simTime = 1.0,
                     const QString& projName = "JsonImport",
                     const QString& targetDir = QDir::homePath());

private:

    void commonLoop(const QString& projName, const QString& targetDir
                    = QDir::homePath(), real simTime = 1.0);

    Data m_data;
};

}

#endif // MAINMODEL_H
