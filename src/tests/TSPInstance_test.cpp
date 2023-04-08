#include "./catch/catch_amalgamated.hpp"
#include "TSPInstance.hpp"

TEST_CASE("Get available vehicles", "[vehicle]")
{
    TSPInstance instance = TSPInstance();
    instance.setUp();
    std::vector<Vehicle> vehicles =
        instance.getAvailableVehiclesForItem(2);
    REQUIRE(vehicles.size() == 2);
}
