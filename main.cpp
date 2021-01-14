#include "architecture/mainmodel.hpp"

#include <QString>

int main(int argc, char* argv[])
{
    volatrack::MainModel model;
    model.runFromJson(argv[1]);
    return 0;
}
