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
    Vehicle *vehicle = new Vehicle(1, 1, 1, 1);
    carrier.addVehicle(vehicle);
    carrier.addClient(1);

    SECTION("Success")
    {
        vehicle->addAcceptedItem(1);
        bool accepts = carrier.acceptsItem(new Item(1, 1, 1, 1));
        REQUIRE(accepts);
    }

    SECTION("Fail - client not in carrier")
    {
        vehicle->addAcceptedItem(1);
        bool accepts = carrier.acceptsItem(new Item(1, 2, 1, 1));
        REQUIRE(!accepts);
    }

    SECTION("Fail - vehicle does not accept item")
    {
        vehicle->addAcceptedItem(2);
        bool accepts = carrier.acceptsItem(new Item(1, 1, 1, 1));
        REQUIRE(!accepts);
    }

    SECTION("Fail - vehicle does not have capacity")
    {
        vehicle->addAcceptedItem(1);
        bool accepts = carrier.acceptsItem(new Item(1, 1, 1, 2));
        REQUIRE(!accepts);
    }
}

TEST_CASE("Get available vehicles", "[vehicle]")
{
    SECTION("Success")
    {
        Carrier carrier = Carrier();
        carrier.addClient(1);
        Vehicle *vehicle = new Vehicle(1, 1, 1, 1);
        vehicle->addAcceptedItem(1);
        carrier.addVehicle(vehicle);
        // std::priority_queue<std::pair<double, Vehicle *>> availableVehicles = carrier.getAvailableVehicles(new Item(1, 1, 1, 1));
        // REQUIRE(availableVehicles.size() == 1);
    }
}

TEST_CASE("Calculate trip cost")
{
    Carrier carrier = Carrier(1, 1, 1, 1);
    carrier.addClient(1);
    Vehicle *vehicle = new Vehicle(1, 1, 1, 1);
    Item *item = new Item(1, 1, 1, 1);
    item->setDestination(new Point(0, 1));
    vehicle->addAcceptedItem(1);
    carrier.addVehicle(vehicle);
    carrier.addFare(1, 1);

    SECTION("Single client 1 km away")
    {
        double cost = carrier.calculateTripCost(item, vehicle);
        double expectedCost = 1 * 1;
        REQUIRE(cost == expectedCost);
    }

    SECTION("Single client sqrt(2) km away")
    {
        item->setDestination(new Point(1, 1));
        double cost = carrier.calculateTripCost(item, vehicle);
        double expectedCost = sqrt(2) * 1;
        REQUIRE(cost == expectedCost);
    }

    SECTION("Single client 0.5 fare")
    {
        carrier.addFare(1, 0.5);
        double cost = carrier.calculateTripCost(item, vehicle);
        double expectedCost = 1 * 0.5;
        REQUIRE(cost == expectedCost);
    }

    SECTION("Single client underweight")
    {
        // TODO: implement
    }

    SECTION("Multiple client")
    {
    }
}