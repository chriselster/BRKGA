#include "./catch/catch_amalgamated.hpp"
#include "../Headers/Vehicle.hpp"

TEST_CASE("Reset")
{
    Vehicle vehicle = Vehicle(1, 1, 1, 1, 1);
    vehicle.addAcceptedItem(1);
    vehicle.take(new Item(1, 1, 1, 1));
    REQUIRE(vehicle.remainingCapacity == 0);
    vehicle.reset();
    REQUIRE(vehicle.remainingCapacity == 1);
}

TEST_CASE("Calculate item cost delta")
{
    Vehicle vehicle = Vehicle(1, 1, 1, 1, 1);
    Item item = Item(1, 1, 1, 1);
    item.setDestination(new Point(0, 2));
    SECTION("Single item")
    {
        REQUIRE(vehicle.calculateTripCostDelta(&item) == 2);
    }
    SECTION("Multiple items")
    {
        vehicle.take(&item);
        Item item2 = Item(1, 2, 1, 1);
        item2.setDestination(new Point(0, 3));
        REQUIRE(vehicle.calculateTripCostDelta(&item2) == 1);
    }
    SECTION("Item in the path")
    {
        vehicle.take(&item);
        Item item2 = Item(1, 2, 1, 1);
        item2.setDestination(new Point(0, 1));
        REQUIRE(vehicle.calculateTripCostDelta(&item2) == 0);
    }
}