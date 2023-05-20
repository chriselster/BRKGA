#include "./catch/catch_amalgamated.hpp"
#include "../Headers/Vehicle.hpp"
#include <vector>

TEST_CASE("Build from value list")
{
    // int id, int type, double capacity,  int carrierId, double costPerKm, double minimumCapacity, double additionalForMultipleClients, max distace
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
    double additionalForMultipleClients = 1;
    double costPerKmPerWeight = 1;
    double itemWeight = 1;
    int minimumCapacity = 1;
    Point *origin = new Point(0, 0);
    Point *destination = new Point(0, 2);
    Vehicle vehicle = Vehicle(1, 1, 1, 100, costPerKmPerWeight, minimumCapacity, additionalForMultipleClients, 10);
    Item item = Item(1, 1, 1, itemWeight);
    item.setDestination(destination);
    double item1TripCost = costPerKmPerWeight * itemWeight * origin->distanceTo(destination);

    SECTION("Single item")
    {
        REQUIRE(vehicle.calculateTripCostDelta(&item) == item1TripCost);
    }
    SECTION("Single item under deadfreight")
    {

        vehicle.setMinimumCapacity(minimumCapacity);
        itemWeight = minimumCapacity - 0.5;
        item.setWeight(itemWeight);
        double deadfreightCost = costPerKmPerWeight * (minimumCapacity - itemWeight) * origin->distanceTo(destination);
        double expectedCost = costPerKmPerWeight * (minimumCapacity - itemWeight) * origin->distanceTo(destination) + deadfreightCost;
        REQUIRE(vehicle.calculateTripCostDelta(&item) == expectedCost);
    }

    SECTION("Multiple items over deadfreight")
    {
        vehicle.take(&item);
        double secondItemWeight = 2;
        destination = new Point(0, 3);
        Item item2 = Item(1, 2, 1, secondItemWeight);
        item2.setDestination(destination);
        double deadfreightCost = costPerKmPerWeight * (minimumCapacity - itemWeight) * origin->distanceTo(destination);
        double expectedCost = costPerKmPerWeight * (secondItemWeight)*origin->distanceTo(destination) + additionalForMultipleClients + item1TripCost;
        REQUIRE(vehicle.calculateTripCostDelta(&item2) == expectedCost - item1TripCost + deadfreightCost);
    }

    SECTION("Multiple items under deadfreight")
    {
        double firstItemWeight = 0.5, secondItemWeight = 0.3;
        int deadfreight = 1;
        vehicle.setMinimumCapacity(deadfreight);
        item.setWeight(firstItemWeight);
        double firstTripCost = vehicle.calculateTripCostDelta(&item);
        double deadfreightCost = costPerKmPerWeight * (minimumCapacity - firstItemWeight) * origin->distanceTo(destination);

        SECTION("Second item still have deadfreight")
        {
            Item item2 = Item(1, 2, 1, secondItemWeight);
            destination = new Point(0, 3);
            item2.setDestination(destination);
            double secondTripCost = origin->distanceTo(destination) * costPerKmPerWeight * (secondItemWeight);
            secondTripCost += origin->distanceTo(destination) * costPerKmPerWeight * (deadfreight - firstItemWeight - secondItemWeight);
            secondTripCost += additionalForMultipleClients;

            vehicle.take(&item);
            REQUIRE(vehicle.calculateTripCostDelta(&item2) == Catch::Approx(secondTripCost - firstTripCost + deadfreightCost));
        }
        SECTION("Second item removes deadfreight")
        {
            secondItemWeight = 0.6;
            Item item2 = Item(1, 2, 1, secondItemWeight);
            destination = new Point(0, 3);
            item2.setDestination(destination);
            double secondTripCost = origin->distanceTo(destination) * costPerKmPerWeight * (secondItemWeight);
            secondTripCost += additionalForMultipleClients;

            vehicle.take(&item);
            REQUIRE(vehicle.calculateTripCostDelta(&item2) == Catch::Approx(secondTripCost - firstTripCost + deadfreightCost));
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