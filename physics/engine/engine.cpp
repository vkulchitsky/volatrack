#include "engine.hpp"
#include "physics/data/constants.hpp"

#include <random>

namespace volatrack {


Engine::Engine() : m_lastSaveTime(0), m_lastJumpCheckTime(0)
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

    for (auto& contact : m_contacts)
    {
        for (auto& vol : data.volatiles())
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
            auto d0 = cst::d0Rel;
            auto jumpProbability = 0.5 * std::exp((-cst::S0 * cst::E0)
                           / (cst::PI * sphere.R * d0 * cst::kB * sphere.T));

            if (dist(*m_gen) < jumpProbability)
            {
                vol.isphere = iOther;
                vol.loc = spOther;
            }
        }
    }
}

void Engine::init(const Data &data)
{
    m_lastSaveTime = data.time.t;
    m_lastJumpCheckTime = data.time.t;
    m_timeVolCoeff = data.time.volCoeff();
    m_contacts = getContacts(data, 0);
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

bool Engine::areNear(const Data &data, Index i, Index j, real dR)
{
    Sphere first = data.spheres()[i];
    Sphere second = data.spheres()[j];

    real totalDistance2 = (first.c - second.c).lengthSquared();

    return (totalDistance2 < std::pow(first.R + second.R + dR, 2));
}

Contacts Engine::getContacts(const Data &data, real dR)
{
    Contacts res;

    for (Index i = 0; i < data.spheres().size(); ++i)
    {
        for (Index j = i; j < data.spheres().size(); ++j)
        {
            if (areNear(data, i, j, dR))
            {
                res.push_back(getContact(i, j, data));
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

Contact Engine::getContact(Index i, Index j, const Data &data)
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

    return {i, spi, j, spj};
}

void Engine::passGen(const std::shared_ptr<std::default_random_engine> &gen)
{
    m_gen = gen;
}

}
