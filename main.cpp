#include "physics/data/sphere.hpp"
#include "physics/data/volatile.hpp"
#include "tests/unittestingframework.hpp"
#include "physics/data/data.hpp"
#include "physics/engine/engine.hpp"
#include "io/projectcontroller.hpp"

#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <iostream>

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

void firstPrint(const Data& data)
{
    const auto& volatiles = data.volatiles();
    const auto& spheres = data.spheres();

    for (Index i = 0; i < volatiles.size(); ++i)
    {
        std::cout << "Absolute volatile location: ("
                  << volatiles[i].absolutePosition(spheres).x() << ", "
                  << volatiles[i].absolutePosition(spheres).y() << ", "
                  << volatiles[i].absolutePosition(spheres).z() << ")"
                  << std::endl;
    }

    std::cout << "----------------------------------------------" << std::endl;

    auto json = data.saveToJson();
    qDebug().noquote() << QJsonDocument{json}.toJson(QJsonDocument::Indented);
}

void firstLoop()
{
    auto data = quickData();

    Engine engine(data);
    ProjectController pc("FirstLoop");
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

void firstRun()
{
    Data data = quickData();
    firstPrint(data);
}

int main()
{
    firstLoop();
    return 0;
}
