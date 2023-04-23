#include "./catch/catch_amalgamated.hpp"
#include "../Headers/Vehicle.hpp"
#include <limits>

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
    double costPerKmPerWeight = 1;
    double itemWeight = 1;
    Point *origin = new Point(0, 0);
    Point *destination = new Point(0, 2);
    Vehicle vehicle = Vehicle(1, 1, 1, 100, costPerKmPerWeight);
    Item item = Item(1, 1, 1, itemWeight);
    item.setDestination(destination);
    SECTION("Single item")
    {
        double expectedCost = costPerKmPerWeight * itemWeight * origin->distanceTo(destination);
        REQUIRE(vehicle.calculateTripCostDelta(&item) == expectedCost);
    }
    SECTION("Single item under deadfreight")
    {
        int minimumCapacity = 1;
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
        itemWeight = 2;
        destination = new Point(0, 3);
        Item item2 = Item(1, 2, 1, itemWeight);
        item2.setDestination(destination);
        double expectedCost = costPerKmPerWeight * itemWeight * origin->distanceTo(destination);
        REQUIRE(vehicle.calculateTripCostDelta(&item2) == expectedCost);
    }

    SECTION("Multiple items under deadfreight")
    {
        double firstItemWeight = 0.5, secondItemWeight = 0.3;
        int deadfreight = 1;
        vehicle.setMinimumCapacity(deadfreight);
        item.setWeight(firstItemWeight);
        double firstTripCost = vehicle.calculateTripCostDelta(&item);

        SECTION("Second item still have deadfreight")
        {
            Item item2 = Item(1, 2, 1, secondItemWeight);
            destination = new Point(0, 3);
            item2.setDestination(destination);
            double secondTripCost = origin->distanceTo(destination) * costPerKmPerWeight * (secondItemWeight) + firstTripCost;
            secondTripCost += origin->distanceTo(destination) * costPerKmPerWeight * (deadfreight - firstItemWeight - secondItemWeight);

            vehicle.take(&item);
            REQUIRE(vehicle.calculateTripCostDelta(&item2) == Catch::Approx(secondTripCost - firstTripCost));
        }
        SECTION("Second item removes deadfreight")
        {
            secondItemWeight = 0.6;
            Item item2 = Item(1, 2, 1, secondItemWeight);
            destination = new Point(0, 3);
            item2.setDestination(destination);
            double secondTripCost = origin->distanceTo(destination) * costPerKmPerWeight * (secondItemWeight) + firstTripCost;

            vehicle.take(&item);
            REQUIRE(vehicle.calculateTripCostDelta(&item2) == Catch::Approx(secondTripCost - firstTripCost));
        }
    }
}
#include "./catch/catch_amalgamated.hpp"