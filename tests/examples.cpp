#include "unittestingframework.hpp"
#include "physics/data/data.hpp"
#include "architecture/mainmodel.hpp"

using namespace volatrack;

TEST(FirstExampleTest)
{
    //
}

TEST(SimpleTestRun)
{
    MainModel model;
    model.setData(Data::quickData());
    model.commonLoop("Test");
}
