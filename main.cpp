#include "physics/data/sphere.hpp"
#include "physics/data/volatile.hpp"
#include "tests/unittestingframework.hpp"
#include <iostream>

using namespace volatrack;

void firstRun()
{
    Spheres spheres;
    Volatiles volatiles;

    spheres.pushSphere(0, 0, 0, 1);
    spheres.pushSphere(0, 0, 2, 0.5);

    volatiles.pushVolatile(0, 0, 0, 1);
    volatiles.pushVolatile(0, 0, 0, -1);
    volatiles.pushVolatile(1, 1, 0, 0);
    volatiles.pushVolatile(1, -1, 0, 0);

    for (Index i = 0; i < volatiles.size(); ++i)
    {
        std::cout << "Absolute volatile location: ("
                  << volatiles[i].absolutePosition(spheres).x() << ", "
                  << volatiles[i].absolutePosition(spheres).y() << ", "
                  << volatiles[i].absolutePosition(spheres).z() << ")"
                  << std::endl;
    }
}

int main()
{
    firstRun();
    return 0;
}
