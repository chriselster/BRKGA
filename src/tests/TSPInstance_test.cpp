#include "./catch/catch_amalgamated.hpp"
#include "../Headers/TSPInstance.hpp"

TEST_CASE("Get available vehicles", "[vehicle]")
{
    double vehicleKmCost = 0.09;
    Point itemPosition = Point(71.704, 34.867);
    TSPInstance instance = TSPInstance();
    instance.setUp();
    instance.attendItem(1, 0.1);
    Catch::Matchers::WithinAbsMatcher matcher = Catch::Matchers::WithinAbsMatcher(vehicleKmCost * itemPosition.distanceTo(new Point(0, 0)), 0.0001);
    REQUIRE_THAT(instance.fitness, matcher);
}

TEST_CASE("Reset")
{
    TSPInstance instance = TSPInstance();
    instance.setUp();
    instance.attendItem(1, 0.1);
    instance.reset();
    REQUIRE(instance.fitness == 0);
}
