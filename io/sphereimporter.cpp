#include "sphereimporter.hpp"
#include "projectcontroller.hpp"

using namespace volatrack;

SphereImporter::SphereImporter()
{

}

SphereImporter::SphereImporter(const QString &path)
{
    m_spheres = spheresFromFile(path);
}

std::vector<Sphere> SphereImporter::spheresFromFile(const QString &path)
{
    return spheresFromObject(objectFromFile(path));
}

QJsonObject SphereImporter::objectFromFile(const QString &path)
{
    return ProjectController::readPath(path);
}

std::vector<Sphere> SphereImporter::spheresFromObject(const QJsonObject &obj)
{
    std::vector<Sphere> res;

    //

    return res;
}
