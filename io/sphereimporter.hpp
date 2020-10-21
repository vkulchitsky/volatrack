/*!
  Imports spheres from jsons files, as exported by polyphysica or others
  @file sphereimporter.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/21/2020
*/

#ifndef SPHEREIMPORTER_H
#define SPHEREIMPORTER_H

#include "physics/data/sphere.hpp"

#include <vector>

#include <QString>
#include <QJsonObject>

namespace volatrack
{

/*!
 * \brief Class for importing spheres from jsons files
 */
class SphereImporter
{
public:
    SphereImporter();
    SphereImporter(const QString& path);

private:
    std::vector<Sphere> spheresFromFile(const QString& path);
    QJsonObject objectFromFile(const QString& path);
    std::vector<Sphere> spheresFromObject(const QJsonObject& obj);

    std::vector<Sphere> m_spheres;
};

}

#endif // SPHEREIMPORTER_H
