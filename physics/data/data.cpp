#include "data.hpp"
#include "defs.hpp"

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

using namespace volatrack;

Data::Data()
{}

Data::Data(const Spheres &&spheres, const Volatiles &&vols)
{
    m_spheres = std::move(spheres);
    m_volatiles = std::move(vols);
}

Spheres Data::spheres() const
{
    return m_spheres;
}

Volatiles Data::volatiles() const
{
    return m_volatiles;
}

void volatrack::Data::pushSphere(const volatrack::Sphere &sphere)
{
    m_spheres.push_back(sphere);
}

void volatrack::Data::pushVolatile(const volatrack::Volatile &vol)
{
    m_volatiles.push_back(vol);
}

QJsonObject Data::saveToJson() const
{
    QJsonObject res;

    // fill spheres
    QJsonArray sphArr;
    for (Index i = 0; i < m_spheres.size(); ++i)
    {
        auto sphObj = m_spheres[i].saveToJson();
        sphArr.insert(i, sphObj);
    }

    // fill volatiles
    QJsonArray volArr;
    for (Index i = 0; i < m_volatiles.size(); ++i)
    {
        auto volObj = m_volatiles[i].saveToJson();
        volArr.insert(i, volObj);
    }

    res.insert(DATA_SPHERES, sphArr);
    res.insert(DATA_VOLS, volArr);
    res.insert(DATA_TIME, time.saveToJson());

    return res;
}

void Data::loadFromJson(const QJsonObject &jo)
{
    spheres().clear();
    volatiles().clear();

    auto sphArr = jo[DATA_SPHERES].toArray();
    auto volArr = jo[DATA_VOLS].toArray();
    auto timeVal = jo[DATA_TIME];

    for (auto sph : sphArr)
    {
        Sphere sphere(0, 0, 0, 1);
        sphere.loadFromJson(sph.toObject());
        m_spheres.push_back(sphere);
    }

    for (auto vol : volArr)
    {
        Volatile volat(0, 1, 0, 0);
        volat.loadFromJson(vol.toObject());
        m_volatiles.push_back(volat);
    }

    time.loadFromJson(timeVal.toObject());
}

void Data::setSpheresArray(const Spheres &&spheres)
{
    m_spheres = std::move(spheres);
}

void Data::setVolatilesArray(const Volatiles &&volatiles)
{
    m_volatiles = volatiles;
}

Data Data::quickData()
{
    Data data;

    data.pushSphere(Sphere(0, 0, 0, 1));
    data.pushSphere(Sphere(0, 0, 2, 0.5));

    data.pushVolatile(Volatile(0, 0, 0, 1));
    data.pushVolatile(Volatile(0, 0, 0, -1));
    data.pushVolatile(Volatile(1, 1, 0, 0));
    data.pushVolatile(Volatile(1, -1, 0, 0));

    return data;
}

void Data::loadSphereEvenly(Index isphere)
{
    //
}
