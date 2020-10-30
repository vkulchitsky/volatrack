#include "architecture/mainmodel.hpp"

int main()
{
    volatrack::MainModel model;
    model.runFromJson("/home/vloot/8sph.json");
    return 0;
}
