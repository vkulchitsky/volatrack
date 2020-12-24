#include "architecture/mainmodel.hpp"

#include <QString>

int main()
{
    QString jsonPath = "/home/vloot/8sph.json";

    volatrack::MainModel model;
//    model.simpleTestRun();
//    model.runFromJson(jsonPath);
//    model.runFromJson(jsonPath, 1, "JsonImportX");
//    model.diffusionTestRun();
//    model.twoSphereJumping();
    model.fiveSphereJumping();
    return 0;
}
