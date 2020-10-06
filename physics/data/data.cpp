#include "data.hpp"

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

    res.insert("spheres", sphArr);
    res.insert("volatiles", volArr);
    res.insert("time", time.saveToJson());

    return res;
}

void Data::loadFromJson(const QJsonObject &jo) const
{
    //
}
