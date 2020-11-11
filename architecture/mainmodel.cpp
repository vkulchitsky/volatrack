#include "mainmodel.hpp"

using namespace volatrack;

MainModel::MainModel()
{
    m_gen = std::make_shared<std::default_random_engine>();
}

void MainModel::commonLoop(const QString &projName, const QString &targetDir,
                           real simTime)
{
    Engine engine;
    engine.passGen(m_gen);
    ProjectController pc(projName, targetDir);
    engine.init(m_data);
    const real endTime = simTime;

    pc.saveToJsonFile(m_data);

    while (m_data.time.t < endTime)
    {
        engine.process(m_data);

        if (engine.needsSaving(m_data))
        {
              pc.saveToJsonFile(m_data);
        }
    }
}

void MainModel::simpleTestRun()
{
    m_data = Data::quickData();
    m_data.passGen(m_gen);
    commonLoop("Test");
}

void MainModel::diffusionTestRun()
{
    m_data = Data::diffusionData();
    m_data.passGen(m_gen);
    commonLoop("DiffusionTest");
}

void MainModel::runFromJson(const QString &runFile, real simTime,
                            const QString &projName, const QString &targetDir)
{
    SphereImporter si(runFile);

    m_data.passGen(m_gen);
    m_data.setSpheresArray(si.spheres());
    m_data.loadSpheresRandomly(7, true);

    commonLoop(projName, targetDir, simTime);
}
