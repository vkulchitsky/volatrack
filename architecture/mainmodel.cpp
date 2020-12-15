#include "mainmodel.hpp"
#include "physics/data/concentration.hpp"

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
        engine.randomWalkProcess(m_data);

        if (engine.needsSaving(m_data))
        {
              pc.saveToJsonFile(m_data);
        }
        if (engine.needsJumpCheck(m_data))
        {
            engine.jumpingProcess(m_data);
        }
    }
}

void MainModel:: scanData()
{
    m_data.passGen(m_gen);
    if (m_data.volGroups().empty())
    {
        VolGroup vg;
        vg.name = "Default";
        vg.color = {0, 1, 0, 1};
        m_data.pushVolGroup(vg);
    }
}

void MainModel::simpleTestRun()
{
    m_data = Data::quickData();
    scanData();
    commonLoop("Test");
}

void MainModel::diffusionTestRun()
{
    m_data = Data::diffusionData();
    scanData();

    commonLoop("DiffusionTest");

    concentration::Concentrations cc(100);
    cc.calculate(m_data, 0);
}

void MainModel::runFromJson(const QString &runFile, real simTime,
                            const QString &projName, const QString &targetDir)
{
    SphereImporter si(runFile);

    scanData();
    m_data.setSpheresArray(si.spheres());
    m_data.loadSpheresRandomly(7, true);

    commonLoop(projName, targetDir, simTime);
}
