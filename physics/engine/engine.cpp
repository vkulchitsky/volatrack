#include "engine.hpp"
#include "physics/data/constants.hpp"

#include <random>

namespace volatrack {


Engine::Engine() : m_lastSaveTime(0)
{
    //
}

Engine::Engine(const Data &data)
{
    init(data);
}

void Engine::process(Data &data)
{
    // every volatile travels sphere distance into a random direction

    auto dist = std::uniform_real_distribution<double>(0, 2 * PI);

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

void Engine::init(const Data &data)
{
    m_lastSaveTime = data.time.t;
    m_timeVolCoeff = data.time.volCoeff();
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

bool Engine::areNear(const Data &data, Index i, Index j, real dR)
{
    Sphere first = data.spheres()[i];
    Sphere second = data.spheres()[j];

    real totalDistance2 = (first.c - second.c).lengthSquared();

    return (totalDistance2 < std::pow(first.R + second.R + dR, 2));
}

Pairs Engine::getContacts(const Data &data, real dR)
{
    Pairs res;

    for (Index i = 0; i < data.spheres().size(); ++i)
    {
        for (Index j = i; j < data.spheres().size(); ++j)
        {
            if (areNear(data, i, j, dR))
            {
                res.push_back({i, j});
            }
        }
    }

    return res;
}

real Engine::stdrdSphDist(Index isphere, const Data& data)
{
    auto& sphere = data.spheres()[isphere];

    // keeping it relative because we will have to divide by R anyway
    auto d0 = d0Rel;

    // volatile travel formula
    return d0 * m_timeVolCoeff * std::exp(-E0 / (2 * kB * sphere.T));
}

void Engine::passGen(const std::shared_ptr<std::default_random_engine> &gen)
{
    m_gen = gen;
}

}
