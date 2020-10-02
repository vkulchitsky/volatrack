#include "unittestingframework.hpp"
#include "physics/data/sphere.hpp"
#include "physics/data/volatile.hpp"

using namespace volatrack;

TEST(absPosTest)
{
    Spheres spheres;
    Volatiles volatiles;

    spheres.pushSphere(0, 0, 0, 1);
    spheres.pushSphere(0, 0, 2, 0.5);

    volatiles.pushVolatile(0, 0, 0, 1);
    volatiles.pushVolatile(0, 0, 0, -1);
    volatiles.pushVolatile(1, 1, 0, 0);
    volatiles.pushVolatile(1, -1, 0, 0);

    ASSERT_EQUAL(volatiles[0].absolutePosition(spheres), vec3(0, 0, 1));
    ASSERT_EQUAL(volatiles[1].absolutePosition(spheres), vec3(0, 0, -1));
    ASSERT_EQUAL(volatiles[2].absolutePosition(spheres), vec3(0.5, 0, 2));
    ASSERT_EQUAL(volatiles[3].absolutePosition(spheres), vec3(-0.5, 0, 2));
}
