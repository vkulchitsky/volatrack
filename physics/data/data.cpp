#include "data.hpp"
#include "defs.hpp"

#include <random>

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

using namespace volatrack;

Data::Data()
{
    std::default_random_engine dre;
    m_gen = std::make_shared<std::default_random_engine>(dre);
}

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

void Data::pushVolGroup(const VolGroup &vg)
{
    m_volGroups.push_back(vg);
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

    // fill groups of volatiles
    QJsonArray vgArr;
    for (Index i = 0; i < m_volGroups.size(); ++i)
    {
        auto vgObj = m_volGroups[i].saveToJson();
        vgArr.insert(i, vgObj);
    }

    res.insert(DATA_SPHERES, sphArr);
    res.insert(DATA_VOLS, volArr);
    res.insert(DATA_VGS, vgArr);
    res.insert(DATA_TIME, time.saveToJson());

    return res;
}

void Data::loadFromJson(const QJsonObject &jo)
{
    spheres().clear();
    volatiles().clear();

    auto sphArr = jo[DATA_SPHERES].toArray();
    auto volArr = jo[DATA_VOLS].toArray();
    auto vgArr = jo[DATA_VGS].toArray();
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

    for (auto vg : vgArr)
    {
        VolGroup vgr;
        vgr.loadFromJson(vg.toObject());
        m_volGroups.push_back(vgr);
    }

    time.loadFromJson(timeVal.toObject());
}

void Data::setSpheresArray(const Spheres &&spheres)
{
    m_spheres = std::move(spheres);
}

void Data::setVolatilesArray(const Volatiles &&volatiles)
{
    m_volatiles = std::move(volatiles);
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

Data Data::diffusionData()
{
    Data data;

    Sphere sph(0, 0, 0, 5);
    sph.T = cst::waterFreeze - 80;
    data.pushSphere(sph);

    Size numVols = 5000;

    for (Index ivol = 0; ivol < numVols; ++ivol)
    {
        data.pushVolatile(Volatile(0, 0, 0, 1));
    }

    return data;
}

void Data::loadSpheresEvenly()
{
    for (Index isphere = 0; isphere < m_spheres.size(); ++isphere)
    {
        loadSphereEvenly(isphere);
    }
}

void Data::loadSpheresRandomly(Size volsPerSphere, bool constVols)
{
    auto dist = std::uniform_int_distribution<Size>(0, 2 * volsPerSphere);

    for (Index isphere = 0; isphere < m_spheres.size(); ++isphere)
    {
        loadSphereRandomly(isphere, constVols ? volsPerSphere : dist(*m_gen));
    }
}

void Data::loadSphereEvenly(Index isphere)
{
    pushVolatile(Volatile{isphere, 0, 0, 1});
    pushVolatile(Volatile{isphere, 0, 0, -1});
    pushVolatile(Volatile{isphere, 0, 1, 0});
    pushVolatile(Volatile{isphere, 0, -1, 0});
    pushVolatile(Volatile{isphere, 1, 0, 0});
    pushVolatile(Volatile{isphere, -1, 0, 0});
}

void Data::loadSphereRandomly(Index isphere, Size number)
{
    for (Index i = 0; i < number; ++i)
    {
        addRandomVolatile(isphere);
    }
}

void Data::addRandomVolatile(Index isphere)
{
    auto dist = std::uniform_real_distribution<double>(-1, 1);

    Volatile vol(isphere, dist(*m_gen), dist(*m_gen), dist(*m_gen));

    if (vol.loc.rect() == vec3{0, 0, 0})
    {
        addRandomVolatile(isphere);
        return;
    }

    vol.loc.normalize();
    m_volatiles.push_back(vol);
}

VolGroups Data::volGroups() const
{
    return m_volGroups;
}

void Data::clearVolGroups()
{
    m_volGroups.clear();
}

void Data::setVolGroupsArray(const VolGroups &&volGroups)
{
    m_volGroups = std::move(volGroups);
}

void Data::passGen(const std::shared_ptr<std::default_random_engine> &gen)
{
    m_gen = gen;
}

Size Data::volsOnSphere(Index isphere)
{
    Size res = 0;

    for (auto& vol : volatiles())
    {
        if (vol.isphere == isphere) res++;
    }

    return res;
}

real Data::concentration(Index isphere, const SurfPoint &sp, real rad)
{
    auto rad2 = rad * rad;
    real volCount = 0;
    auto sphere = m_spheres[isphere];
    auto sphR2 = sphere.R * sphere.R;

    for (auto& vol : m_volatiles)
    {
        if (vol.isphere != isphere) continue;

        if ((vol.loc.rect() - sp.rect()).lengthSquared() * sphR2 < rad2)
        {
            volCount++;
        }
    }

    return volCount / (cst::PI * rad2);
}
