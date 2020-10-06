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

}
