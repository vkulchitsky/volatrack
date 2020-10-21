#include "physics/data/sphere.hpp"
#include "physics/data/volatile.hpp"
#include "tests/unittestingframework.hpp"
#include "physics/data/data.hpp"
#include "physics/engine/engine.hpp"
#include "io/projectcontroller.hpp"
#include "io/sphereimporter.hpp"

#include <iostream>

#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>

using namespace volatrack;

Data quickData()
{
    Data data;

    data.pushSphere(Sphere(0, 0, 0, 1));
    data.pushSphere(Sphere(0, 0, 2, 0.5));

    data.pushVolatile(Volatile(0, 0, 0, 1));
    data.pushVolatile(Volatile(0, 0, 0, -1));
    data.pushVolatile(Volatile(1, 1, 0, 0));
    data.pushVolatile(Volatile(1, -1, 0, 0));

    return data;
}

void commonLoop(const QString& projName, Data&& data,
                const QString& sourceDir = QDir::homePath())
{
    Engine engine;
    ProjectController pc(projName, sourceDir);
    engine.init(data);
    const real endTime = 1.0;

    pc.saveToJsonFile(data);

    while (data.time.t < endTime)
    {
        engine.process(data);

        if (engine.needsSaving(data))
        {
              pc.saveToJsonFile(data);
        }
    }
}

void firstLoopRun()
{
    commonLoop("FirstLoop", quickData());
}

void secondLoopRun()
{
    // enter a path into sphere importer
    SphereImporter si("/home/vladimir/ss4.json");

    // get spheres from importer
    //

    // pack spheres into data, and add a few volatiles along the way
    //

    // take "SecondLoop" and the received data through the common loop
    //
}

int main()
{
    secondLoopRun();
    return 0;
}
