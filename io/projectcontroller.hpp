/*!
  Ability to save data into files and control the project
  @file projectcontroller.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/06/2020
*/

#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include "physics/engine/engine.hpp"
#include "physics/data/data.hpp"

#include <QStringList>
#include <QVector>
#include <QJsonObject>

namespace volatrack {

struct DataFile
{
    Data data;
    QString path;
};


/*!
 * \brief Controller for saving data into files
 */
class ProjectController
{
public:

    /*!
     * \brief Constructor with name and source directory
     */
    ProjectController(const QString& name, const QString& sourceDir = {});

    /*!
     * \brief Simple constructor
     */
    ProjectController();

    /*!
     * \brief sets file paths to those selected
     * \param files - string list of files
     */
    void setFiles(const QStringList&& files);

    /*!
     * \brief getter for a specific stored path
     * \param i - index
     * \return the path stored under that index
     */
    QString getPath(Index i);

    /*!
     * \brief data from path
     * \param i - index
     * \return the data from path stored under that index
     */
    Data getData(Index i);

    /*!
     * \brief save data to json file
     * \param data
     */
    void saveToJsonFile(const Data& data);

private:

    QJsonObject readPath(const QString& path);
    void readFiles();

    QStringList m_files;
    QString m_name;
    QString m_sourceDir;
    QVector<QJsonObject> m_jsons;
};

}

#endif // PROJECTCONTROLLER_H
