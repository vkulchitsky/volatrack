#include "architecture/mainmodel.hpp"

int main()
{
    volatrack::MainModel model;
    model.runFromJson("/home/vloot/8sph.json", 1, "JsonImportX");
    return 0;
}
