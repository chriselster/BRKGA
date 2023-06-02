#include "./catch/catch_amalgamated.hpp"
#include "../Headers/Vehicle.hpp"
#include <vector>

TEST_CASE("Build from value list")
{
    // int id, int type, long double capacity,  int carrierId, long double costPerKm, long double minimumCapacity, long double additionalForMultipleClients, max distace
    std::vector<std::string> values = {"1", "3", "0.1", "2", "0.2", "0.3", "0.4", "0.5"};
    Vehicle vehicle = Vehicle(values);
    REQUIRE(vehicle.id == 1);
    REQUIRE(vehicle.carrierId == 2);
    REQUIRE(vehicle.type == 3);
    REQUIRE(vehicle.remainingCapacity == 0.1);
}

TEST_CASE("Reset")
{
    Vehicle vehicle = Vehicle(1, 1, 1, 1, 1, 1, 1, 1);
    vehicle.addAcceptedItem(1);
    vehicle.take(new Item(1, 1, 1, 1));
    REQUIRE(vehicle.remainingCapacity == 0);
    vehicle.reset();
    REQUIRE(vehicle.remainingCapacity == 1);
}

TEST_CASE("Calculate item cost delta")
{
    long double additionalForMultipleClients = 1;
    long double costPerKmPerWeight = 1;
    long double itemWeight = 1;
    int minimumCapacity = 1;
    Point *origin = new Point(0, 0);
    Point *destination = new Point(0, 2);
    Vehicle vehicle = Vehicle(1, 1, 1, 100, costPerKmPerWeight, minimumCapacity, additionalForMultipleClients, 10);
    Item item = Item(1, 1, 1, itemWeight);
    item.setDestination(destination);
    long double item1TripCost = costPerKmPerWeight * itemWeight * origin->distanceTo(destination);

    SECTION("Single item")
    {
        REQUIRE(vehicle.calculateTripCostDelta(&item) == item1TripCost);
    }
    SECTION("Single item under deadfreight")
    {
        vehicle.setMinimumCapacity(minimumCapacity);
        itemWeight = minimumCapacity - 0.5;
        item.setWeight(itemWeight);
        vehicle.take(&item);
        long double expectedCost = vehicle.tripCost();
        vehicle.reset();
        REQUIRE(vehicle.calculateTripCostDelta(&item) == expectedCost);
    }

    SECTION("Multiple items over deadfreight")
    {
        vehicle.take(&item);
        long double costOfFirstItem = vehicle.tripCost();
        long double secondItemWeight = 2;
        destination = new Point(0, 3);
        Item item2 = Item(1, 2, 1, secondItemWeight);
        item2.setDestination(destination);
        vehicle.take(&item2);
        long double costOfTakingBoth = vehicle.tripCost();
        vehicle.reset();
        vehicle.take(&item);
        REQUIRE(vehicle.calculateTripCostDelta(&item2) == costOfTakingBoth - costOfFirstItem);
    }

    SECTION("Multiple items under deadfreight")
    {
        long double firstItemWeight = 0.5, secondItemWeight = 0.3;
        int deadfreight = 1;
        vehicle.setMinimumCapacity(deadfreight);
        item.setWeight(firstItemWeight);
        long double firstTripCost = vehicle.calculateTripCostDelta(&item);

        SECTION("Second item still have deadfreight")
        {
            Item item2 = Item(1, 2, 1, secondItemWeight);
            destination = new Point(0, 3);
            item2.setDestination(destination);
            vehicle.take(&item);
            vehicle.take(&item2);
            long double costOfTakingBoth = vehicle.tripCost();
            vehicle.reset();
            vehicle.take(&item);
            REQUIRE(vehicle.calculateTripCostDelta(&item2) == Catch::Approx(costOfTakingBoth - firstTripCost));
        }

        SECTION("Second item removes deadfreight")
        {
            secondItemWeight = 0.6;
            Item item2 = Item(1, 2, 1, secondItemWeight);
            destination = new Point(0, 3);
            item2.setDestination(destination);
            vehicle.take(&item);
            vehicle.take(&item2);
            long double costOfTakingBoth = vehicle.tripCost();
            vehicle.reset();
            vehicle.take(&item);
            REQUIRE(vehicle.calculateTripCostDelta(&item2) == Catch::Approx(costOfTakingBoth - firstTripCost));
        }
    }
}

TEST_CASE("Can attend")
{
    Vehicle vehicle = Vehicle(1, 1, 1, 40, 1, 1, 1, 5);
    vehicle.addAcceptedItem(1);
    Item item = Item(1, 1, 1, 1);
    item.setDestination(new Point(0, 1));
    vehicle.take(&item);
    SECTION("True if is to same client")
    {
        item = Item(1, 1, 1, 1);
        REQUIRE(vehicle.canTake(&item));
    }
    SECTION("False if is to different client far away")
    {
        Item item = Item(1, 2, 1, 1);
        item.setDestination(new Point(0, 20));
        REQUIRE(!vehicle.canTake(&item));
    }
    SECTION("Unless other client is in range")
    {
        Item item = Item(1, 2, 1, 1);
        item.setDestination(new Point(0, 2));
        REQUIRE(vehicle.canTake(&item));
    }
}

#include "./catch/catch_amalgamated.hpp"