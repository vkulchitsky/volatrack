#include "physics/data/data.hpp"
#include "architecture/mainmodel.hpp"

using namespace volatrack;

void simpleTestRun()
{
    MainModel model;
    model.setData(Data::quickData());
    model.commonLoop("Test");
}

int main()
{
    simpleTestRun();
}
