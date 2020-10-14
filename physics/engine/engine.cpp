#include "engine.hpp"
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
    data.time.t += data.time.dt;
}

void Engine::init(const Data &data)
{
    m_lastSaveTime = data.time.t;
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
    Sphere&  first = data.spheres()[i];
    Sphere& second = data.spheres()[j];

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

}
