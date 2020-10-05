#include "unittestingframework.hpp"
#include "physics/data/sphere.hpp"
#include "physics/data/volatile.hpp"

using namespace volatrack;

TEST(absPosTest)
{
    Spheres spheres;
    Volatiles volatiles;

    spheres.push_back(Sphere(0, 0, 0, 1));
    spheres.push_back(Sphere(0, 0, 2, 0.5));

    volatiles.push_back(Volatile(0, 0, 0, 1));
    volatiles.push_back(Volatile(0, 0, 0, -1));
    volatiles.push_back(Volatile(1, 1, 0, 0));
    volatiles.push_back(Volatile(1, -1, 0, 0));

    ASSERT_EQUAL(volatiles[0].absolutePosition(spheres), vec3(0, 0, 1));
    ASSERT_EQUAL(volatiles[1].absolutePosition(spheres), vec3(0, 0, -1));
    ASSERT_EQUAL(volatiles[2].absolutePosition(spheres), vec3(0.5, 0, 2));
    ASSERT_EQUAL(volatiles[3].absolutePosition(spheres), vec3(-0.5, 0, 2));
}
