#include "./catch/catch_amalgamated.hpp"
#include "../Headers/TSPInstance.hpp"

TEST_CASE("Reset")
{
    TSPInstance instance = TSPInstance();
    instance.setUp();
    instance.attendItem(1, 0.1);
    instance.reset();
    REQUIRE(instance.fitness == 0);
}

TEST_CASE("Set up")
{
    TSPInstance instance = TSPInstance();
    instance.setUp();
    instance.print();
}
