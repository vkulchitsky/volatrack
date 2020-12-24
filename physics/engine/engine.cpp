#include "engine.hpp"
#include "physics/data/constants.hpp"

#include <random>

namespace volatrack {


Engine::Engine() : m_lastSaveTime(0), m_lastJumpCheckTime(0)
  , m_jumpingAngle(cst::PI)
{
    //
}

Engine::Engine(const Data &data)
{
    init(data);
}

void Engine::randomWalkProcess(Data &data)
{
    // every volatile travels sphere distance into a random direction

    auto dist = std::uniform_real_distribution<double>(0, 2 * cst::PI);

    Volatiles newVols = data.volatiles();

    for (auto& vol : newVols)
    {
        // find out distance that volatile needs to travel
        const auto& d = stdrdSphDist(vol.isphere, data);

        // go d in random direction on the great circle
        vol.loc.moveBy(d, dist(*m_gen));
    }

    data.setVolatilesArray(std::move(newVols));

    data.time.t += data.time.dt;
}

void Engine::jumpingProcess(Data &data)
{
    auto dist = std::uniform_real_distribution<double>(0, 1);

    auto vols = data.volatiles();

    for (auto& contact : m_contacts)
    {
        for (auto& vol : vols)
        {
            if (vol.isphere != contact.i && vol.isphere != contact.j) continue;
            Index iCurr = vol.isphere;
            Index iOther;
            if (iCurr == contact.i)
            {
                iOther = contact.j;
            }
            else
            {
                iOther = contact.i;
            }
            SurfPoint spCurr = contact.pointOf(iCurr);
            SurfPoint spOther = contact.pointOf(iOther);
            if (spCurr.angleWith(vol.loc) > m_jumpingAngle) continue;

            auto sphere = data.spheres()[vol.isphere];

            auto jumpProbability = 0.5 * std::exp((-cst::S0 * cst::E0)
                           / (contact.csArea(data) * cst::kB * sphere.T));

            if (dist(*m_gen) < jumpProbability)
            {
                vol.isphere = iOther;
                vol.loc = spOther;
            }
        }
    }

    data.setVolatilesArray(std::move(vols));
}

void Engine::init(const Data &data)
{
    m_lastSaveTime = data.time.t;
    m_lastJumpCheckTime = data.time.t;
    m_timeVolCoeff = data.time.volCoeff();
    m_contacts = getContacts(data);
    m_dR = 0.01;
    m_jumpingAngle = cst::PI / 180;
}

bool Engine::needsSaving(const Data &data)
{
    if (data.time.t - m_lastSaveTime > data.time.dtSave)
    {
        m_lastSaveTime = data.time.t;
        return true;
    }

    return false;
}

bool Engine::needsJumpCheck(const Data &data)
{
    if (data.time.t - m_lastJumpCheckTime > data.time.dtJump)
    {
        m_lastJumpCheckTime = data.time.t;
        return true;
    }

    return false;
}

real Engine::intersection(const Data &data, Index i, Index j)
{
    Sphere first = data.spheres()[i];
    Sphere second = data.spheres()[j];

    if ((first.c - second.c).lengthSquared() > std::pow(first.R + second.R, 2))
    {
        return -1;
    }

    real totalDistance = (first.c - second.c).length();

    return first.R + second.R - totalDistance;
}

Contacts Engine::getContacts(const Data &data)
{
    Contacts res;

    for (Index i = 0; i < data.spheres().size(); ++i)
    {
        for (Index j = i + 1; j < data.spheres().size(); ++j)
        {
            auto intersect = intersection(data, i, j);
            if (intersect > 0)
            {
                res.push_back(getContact(i, j, intersect, data));
            }
        }
    }

    return res;
}

real Engine::stdrdSphDist(Index isphere, const Data& data)
{
    auto& sphere = data.spheres()[isphere];

    // keeping it relative because we will have to divide by R anyway
    auto d0 = cst::d0Rel;

    // volatile travel formula
    return d0 * m_timeVolCoeff * std::exp(-cst::E0 / (2 * cst::kB * sphere.T));
}

Contact Engine::getContact(Index i, Index j, real delta, const Data &data)
{
    auto sphi = data.spheres()[i];
    auto sphj = data.spheres()[j];

    SurfPoint spi(sphj.c - sphi.c);
    spi.normalize();
    spi.rotateBy(sphi.q.inverse());
    spi.normalize();

    SurfPoint spj(sphi.c - sphj.c);
    spj.normalize();
    spj.rotateBy(sphj.q.inverse());
    spj.normalize();

    return {i, spi, j, spj, delta};
}

void Engine::passGen(const std::shared_ptr<std::default_random_engine> &gen)
{
    m_gen = gen;
}

}
