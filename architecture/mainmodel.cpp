#include "mainmodel.hpp"

using namespace volatrack;

MainModel::MainModel()
{

}

void MainModel::commonLoop(const QString &projName, const QString &targetDir,
                           real simTime)
{
    Engine engine;
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
    commonLoop("QuickDataSim");
}

void MainModel::runFromJson(const QString &runFile, real simTime,
                            const QString &projName, const QString &targetDir)
{
    SphereImporter si(runFile);

    m_data.setSpheresArray(si.spheres());

    for (Index i = 0; i < m_data.spheres().size(); ++i)
    {
        m_data.pushVolatile(Volatile{i, 0, 0, 1});
        m_data.pushVolatile(Volatile{i, 0, 0, -1});
        m_data.pushVolatile(Volatile{i, 0, 1, 0});
        m_data.pushVolatile(Volatile{i, 0, -1, 0});
        m_data.pushVolatile(Volatile{i, 1, 0, 0});
        m_data.pushVolatile(Volatile{i, -1, 0, 0});
    }

    // take "SecondLoop" and the received data through the common loop
    commonLoop(projName, targetDir, simTime);
}
