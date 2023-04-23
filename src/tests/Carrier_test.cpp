#include "./catch/catch_amalgamated.hpp"
#include "../Headers/Carrier.hpp"
#include "../Headers/Client.hpp"
#include "../Headers/Vehicle.hpp"
#include "../Headers/Item.hpp"
#include <queue>
#include <utility>

TEST_CASE("Check if can attend item", "[item]")
{
    Carrier carrier = Carrier();
    Vehicle *vehicle = new Vehicle(1, 1, 1, 1, 0.5, 0.2, 20);
    carrier.addVehicle(vehicle);
    carrier.addClient(1);

    SECTION("Success")
    {
        vehicle->addAcceptedItem(1);
        bool accepts = carrier.canAttend(new Item(1, 1, 1, 1));
        REQUIRE(accepts);
    }

    SECTION("Fail - client not in carrier")
    {
        vehicle->addAcceptedItem(1);
        bool accepts = carrier.canAttend(new Item(1, 2, 1, 1));
        REQUIRE(!accepts);
    }

    SECTION("Fail - vehicle does not accept item")
    {
        vehicle->addAcceptedItem(2);
        bool accepts = carrier.canAttend(new Item(1, 1, 1, 1));
        REQUIRE(!accepts);
    }

    SECTION("Fail - vehicle does not have capacity")
    {
        vehicle->addAcceptedItem(1);
        bool accepts = carrier.canAttend(new Item(1, 1, 1, 2));
        REQUIRE(!accepts);
    }
}

TEST_CASE("Get available vehicles", "[vehicle]")
{
    SECTION("Success")
    {
        Carrier carrier = Carrier();
        carrier.addClient(1);
        Vehicle *vehicle = new Vehicle(1, 1, 1, 1, 1, 1, 1);
        vehicle->addAcceptedItem(1);
        carrier.addVehicle(vehicle);
        std::priority_queue<std::pair<double, Vehicle *>> availableVehicles = carrier.getAvailableVehicles(new Item(1, 1, 1, 1));
        REQUIRE(availableVehicles.size() == 1);
    }
}

TEST_CASE("Calculate trip cost")
{
    double COST_PER_ADDITIONAL_CLIENT = 1000;
    double MINIMUM_CAPACITY = 1;
    double DEAD_FREIGHT_COST = 10;
    double COST_PER_KM = 5;
    Carrier carrier = Carrier(1);
    carrier.addClient(1);
    Vehicle *vehicle = new Vehicle(1, 1, 1, 10, COST_PER_KM, 1, 1);
    Item *item = new Item(1, 1, 1, 1);
    item->setDestination(new Point(0, 20));
    vehicle->addAcceptedItem(1);
    carrier.addVehicle(vehicle);

    SECTION("Single client 20 km away")
    {
        double cost = carrier.calculateTripCostDelta(item, vehicle);
        double expectedCost = 20 * COST_PER_KM;
        REQUIRE(cost == expectedCost);
    }

    SECTION("Single client underweight")
    {
        Item *item = new Item(1, 1, 1, 0.5);
        item->setDestination(new Point(0, 4));
        double cost = carrier.calculateTripCostDelta(item, vehicle); // did not exceed the minimum capacity
        double expectedCost = vehicle->calculateTripCostDelta(item);
        REQUIRE(cost == expectedCost);
    }

    SECTION("Multiple client")
    {
        carrier.attendItem(item, vehicle);
        item = new Item(2, 2, 1, 1);
        item->setDestination(new Point(0, 4));
        double cost = carrier.calculateTripCostDelta(item, vehicle);
        double expectedCost = vehicle->calculateTripCostDelta(item);
        REQUIRE(cost == expectedCost);
    }
}

TEST_CASE("Attend item")
{
    Carrier carrier = Carrier(1);
    carrier.addClient(1);
    Vehicle *vehicle = new Vehicle(1, 1, 1, 1, 1, 1, 1);
    Item *item = new Item(1, 1, 1, 1);
    item->setDestination(new Point(0, 1));
    vehicle->addAcceptedItem(1);
    carrier.addVehicle(vehicle);
    carrier.attendItem(item, vehicle);
    REQUIRE(vehicle->remainingCapacity == 1 - item->weight);
}