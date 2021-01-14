/*!
  Use this file to create example scenarios for testing
  The main program should have user input
  This file is for the developer to create new test cases and examples
*/

#include "physics/data/data.hpp"
#include "architecture/mainmodel.hpp"
#include "physics/data/concentration.hpp"

#include <memory>
#include <iostream>

using namespace volatrack;

void simpleTestRun()
{
    MainModel model(Data::quickData());
    model.commonLoop("Test");
}

void diffusionTestRun()
{
    MainModel model(Data::diffusionData());

    model.commonLoop("DiffusionTest");

    concentration::Concentrations cc(100);
    cc.calculate(model.data(), 0);
}

void twoSphereJumping()
{
    Data data;

    const real delta = 0.05;

    Sphere rs(1 - delta * 0.5, 0, 0, 1);
    Sphere ls(-1 + delta * 0.5, 0, 0, 1);
    rs.T = cst::waterFreeze - 80;
    ls.T = cst::waterFreeze + 500;
    data.pushSphere(rs);
    data.pushSphere(ls);

    VolGroup rightGroup;
    rightGroup.color = {0, 0, 1, 1};
    rightGroup.name = "Right initial";

    VolGroup leftGroup;
    leftGroup.color = {0, 1, 0, 1};
    leftGroup.name = "Left initial";

    data.loadSpheresRandomly(20, true);

    data.clearVolGroups();

    data.pushVolGroup(rightGroup);
    data.pushVolGroup(leftGroup);

    auto vols = data.volatiles();

    for (auto& vol : vols)
    {
        vol.igroup = vol.isphere;
    }

    data.setVolatilesArray(std::move(vols));

    MainModel model(data);

    model.commonLoop("ExamplesTSJ", QDir::homePath(), 20.0);

    std::cout << "Volatiles on left sphere: " << model.data().volsOnSphere(1)
              << std::endl;
    std::cout << "Volatiles on right sphere: " << model.data().volsOnSphere(0)
              << std::endl;
}

void fiveSphereJumping()
{
    Data data;

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

    data.pushSphere(A);
    data.pushSphere(B);
    data.pushSphere(C);
    data.pushSphere(D);
    data.pushSphere(E);

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

    data.loadSpheresRandomly(20, true);

    data.clearVolGroups();

    data.pushVolGroup(gA);
    data.pushVolGroup(gB);
    data.pushVolGroup(gC);
    data.pushVolGroup(gD);
    data.pushVolGroup(gE);

    auto vols = data.volatiles();

    for (auto& vol : vols)
    {
        vol.igroup = vol.isphere;
    }

    data.setVolatilesArray(std::move(vols));

    MainModel model(data);

    model.commonLoop("ExampleFSJ", QDir::homePath(), 10.0);
}

void imported8Spheres()
{
    QString jsonPath = "/home/vloot/8sph.json";
    MainModel model;
    model.runFromJson(jsonPath, 1, "8sph");
}

int main()
{
//    simpleTestRun();
//    diffusionTestRun();
//    twoSphereJumping();
//    fiveSphereJumping();
    imported8Spheres();
}
