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


/*!
 * \brief Controller for saving data into files
 */
class ProjectController
{
public:
    ProjectController(const QString& name, const QString& sourceDir = {});
    ProjectController();

    void setFiles(const QStringList&& files);
    QString getPath(Index i);
//    QJsonObject
    void readFiles();

    Index iCurrentFile;

    /*!
     * \brief save data to json file
     * \param data
     */
    void saveToJsonFile(const Data& data);

private:

    QJsonObject readPath(const QString& path);

    QStringList m_files;
    QString m_name;
    QString m_sourceDir;
    QVector<QJsonObject> m_jsons;
};

}

#endif // PROJECTCONTROLLER_H
