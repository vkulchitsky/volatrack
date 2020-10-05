#include "data.h"

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

QJsonObject Data::saveToJson()
{
    QJsonObject res;
    QJsonArray sphArr;
    QJsonArray volArr;

    // fill spheres

    for (Index i = 0; i < m_spheres.size(); ++i)
    {
        auto& sph = m_spheres[i];
        QJsonObject sphObj;

        // position
        QJsonArray posArr = {sph.c.x(), sph.c.y(), sph.c.z()};
        sphObj.insert("position", posArr);

        // radius and temperature
        sphObj.insert("radius", sph.R);
        sphObj.insert("temperature", sph.T);

        // material
//        QJsonObject matObj;
//        auto& mat = sph.material;
//        matObj.insert("rho", mat.rho);
//        matObj.insert("G", mat.G);
//        matObj.insert("nu", mat.nu);
//        matObj.insert("gamma", mat.gamma);
//        matObj.insert("CR0", mat.CR0);
//        matObj.insert("vR0", mat.vR0);
//        matObj.insert("alpha_t", mat.alpha_t);
//        matObj.insert("mu", mat.mu);
//        matObj.insert("rMu", mat.rMu);
//        matObj.insert("rNu", mat.rNu);
//        matObj.insert("rK", mat.rK);
//        matObj.insert("rTh", mat.rTh);
//        matObj.insert("visc", mat.visc);
//        matObj.insert("viscg", mat.viscg);
//        matObj.insert("name", QString::fromStdString(mat.name));
//        sphObj.insert("material", matObj);

        sphObj.insert("material", sph.material.saveToJson());

        sphArr.insert(i, sphObj);
    }

    // fill volatiles

    for (Index i = 0; i < m_volatiles.size(); ++i)
    {
        auto& vol = m_volatiles[i];
        QJsonObject volObj;

        // sphere index
        volObj.insert("isphere", static_cast<int>(vol.isphere));

        // surface location
        QJsonArray surfLocArr = {vol.loc.rect().x(), vol.loc.rect().y(),
                                vol.loc.rect().z()};
        volObj.insert("surface location", surfLocArr);

        // flags
        volObj.insert("flags", static_cast<int>(vol.flags));

        volArr.insert(i, volObj);
    }

    res.insert("spheres", sphArr);
    res.insert("volatiles", volArr);

    return res;
}

void Data::loadFromJson(const QJsonObject &jo)
{
    //
}
