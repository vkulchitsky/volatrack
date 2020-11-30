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

void Engine::jumpingProcess(Data &data)
{
    real dR = 0.01;
    auto contacts = getContacts(data, dR);

    for (auto& pair : contacts)
    {
        //
    }
}

void Engine::init(const Data &data)
{
    m_lastSaveTime = data.time.t;
    m_lastJumpCheckTime = data.time.t;
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
                // get transformation matrix from polyphysica
                auto sphi = data.spheres()[i];
                auto sphj = data.spheres()[j];

                auto Ti = rotMat(sphi.q);
                auto Tj = rotMat(sphj.q);

                // ASSUMING SPHERES ARE NOT ORIENTED

                SurfPoint s1(sphj.c - sphi.c);
                s1.normalize();
                SurfPoint s2(sphi.c - sphj.c);
                s2.normalize();

                res.push_back({i, s1, j, s2});
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

std::vector<quat> Engine::rotMat(quat q)
{
    float xx{ 2*q.x()*q.x() }, yy{ 2*q.y()*q.y() }, zz{ 2*q.z()*q.z() },
          xy{ 2*q.x()*q.y() }, xz{ 2*q.x()*q.z() }, yz{ 2*q.y()*q.z() },
          xw{ 2*q.x()*q.w() }, yw{ 2*q.y()*q.w() }, zw{ 2*q.z()*q.w() };

    return {{1-(yy+zz),    xy-zw,     xz+yw,  0},
               {xy+zw,  1-(xx+zz),    yz-xw,  0},
               {xz-yw,     yz+xw,  1-(xx+yy), 0},
                   {0,         0,          0, 1}};
}

void Engine::passGen(const std::shared_ptr<std::default_random_engine> &gen)
{
    m_gen = gen;
}

}
