#include "mainmodel.hpp"
#include "physics/data/concentration.hpp"

#include <iostream>

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

Data MainModel::data() const
{
    return m_data;
}

void MainModel::setData(const Data &data)
{
    m_data = data;
    scanData();
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

void MainModel::twoSphereJumping()
{
    m_data.passGen(m_gen);

    const real delta = 0.05;

    Sphere rs(1 - delta * 0.5, 0, 0, 1);
    Sphere ls(-1 + delta * 0.5, 0, 0, 1);
    rs.T = cst::waterFreeze - 80;
    ls.T = cst::waterFreeze + 500;
    m_data.pushSphere(rs);
    m_data.pushSphere(ls);

    VolGroup rightGroup;
    rightGroup.color = {0, 0, 1, 1};
    rightGroup.name = "Right initial";

    VolGroup leftGroup;
    leftGroup.color = {0, 1, 0, 1};
    leftGroup.name = "Left initial";

    scanData();

    m_data.loadSpheresRandomly(20, true);

    m_data.clearVolGroups();

    m_data.pushVolGroup(rightGroup);
    m_data.pushVolGroup(leftGroup);

    auto vols = m_data.volatiles();

    for (auto& vol : vols)
    {
        vol.igroup = vol.isphere;
    }

    m_data.setVolatilesArray(std::move(vols));

    commonLoop("FirstJumpingTest", QDir::homePath(), 20.0);

    std::cout << "Volatiles on left sphere: " << m_data.volsOnSphere(1)
              << std::endl;
    std::cout << "Volatiles on right sphere: " << m_data.volsOnSphere(0)
              << std::endl;
}

void MainModel::fiveSphereJumping()
{
    m_data.passGen(m_gen);

    const real delta = 0.05;

    Sphere A(-4 + 2 * delta, 0, 0, 1);
    Sphere B(-2 + delta, 0, 0, 1);
    Sphere C(0, 0, 0, 1);
    Sphere D(2 - delta, 0, 0, 1);
    Sphere E(4 - 2 * delta, 0, 0, 1);

    A.T = cst::waterFreeze - 100;
    B.T = cst::waterFreeze + 300;
    C.T = cst::waterFreeze + 200;
    D.T = cst::waterFreeze + 100;
    E.T = cst::waterFreeze;

    m_data.pushSphere(A);
    m_data.pushSphere(B);
    m_data.pushSphere(C);
    m_data.pushSphere(D);
    m_data.pushSphere(E);

    VolGroup gA, gB, gC, gD, gE;

    gA.color = {0, 0, 1, 1};
    gA.name = "A";

    gB.color = {0, 1, 0, 1};
    gB.name = "B";

    gC.color = {1, 1, 0, 1};
    gC.name = "C";

    gD.color = {0, 0, 0, 1};
    gD.name = "D";

    gE.color = {1, 1, 1, 1};
    gE.name = "E";

    scanData();

    m_data.loadSpheresRandomly(20, true);

    m_data.clearVolGroups();

    m_data.pushVolGroup(gA);
    m_data.pushVolGroup(gB);
    m_data.pushVolGroup(gC);
    m_data.pushVolGroup(gD);
    m_data.pushVolGroup(gE);

    auto vols = m_data.volatiles();

    for (auto& vol : vols)
    {
        vol.igroup = vol.isphere;
    }

    m_data.setVolatilesArray(std::move(vols));

    commonLoop("SecondJumpingTest", QDir::homePath(), 10.0);
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
