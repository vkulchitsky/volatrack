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

void lameLoopRun()
{
    Data data;
    data.pushSphere(Sphere(0, 0, 0, 1));

    data.pushVolatile(Volatile{0, 0, 0, 1});
    data.pushVolatile(Volatile{0, 0, 0, -1});
    data.pushVolatile(Volatile{0, 0, 1, 0});
    data.pushVolatile(Volatile{0, 0, -1, 0});
    data.pushVolatile(Volatile{0, 1, 0, 0});
    data.pushVolatile(Volatile{0, -1, 0, 0});

    commonLoop("LameLoop", std::move(data));
}

void firstLoopRun()
{
    commonLoop("FirstLoop", quickData());
}

void secondLoopRun()
{
    SphereImporter si("/home/vladimir/8sph.json");

    Data data;
    data.setSpheresArray(si.spheres());

    for (Index i = 0; i < data.spheres().size(); ++i)
    {
        data.pushVolatile(Volatile{i, 0, 0, 1});
        data.pushVolatile(Volatile{i, 0, 0, -1});
        data.pushVolatile(Volatile{i, 0, 1, 0});
        data.pushVolatile(Volatile{i, 0, -1, 0});
        data.pushVolatile(Volatile{i, 1, 0, 0});
        data.pushVolatile(Volatile{i, -1, 0, 0});
    }

    // take "SecondLoop" and the received data through the common loop
    commonLoop("SecondLoop", std::move(data));
}

int main()
{
    secondLoopRun();
    return 0;
}
