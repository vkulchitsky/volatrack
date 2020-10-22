#include "sphereimporter.hpp"
#include "projectcontroller.hpp"

#include <random>

#include <QJsonArray>

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

    auto gen = std::default_random_engine();
    real increment = 100.0;
    auto dist = std::uniform_real_distribution<double>(waterFreeze - increment,
                                                       waterFreeze + increment);

    for (int i = 0; i < obj["spheres"].toObject().length(); ++i)
    {
        const auto& sph = obj["spheres"].toObject()[QString::number(i)];

        Sphere sphere(0, 0, 0, 1);
        sphere.loadFromJson(sph.toObject());
        sphere.T = dist(gen);

        // we leave the material blank for now

        res.push_back(sphere);
    }

    return res;
}

std::vector<Sphere> SphereImporter::spheres() const
{
    return m_spheres;
}
