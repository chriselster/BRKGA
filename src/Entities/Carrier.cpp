#include "Carrier.hpp"

Carrier::Carrier(int id) : id(id)
{
}

Carrier::Carrier()
{
    id = 0;
}

Carrier::~Carrier()
{
}

void Carrier::addClient(int clientId)
{
    clientIds.insert(clientId);
}

void Carrier::addVehicle(Vehicle *vehicle)
{
    vehicles.push_back(vehicle);
}

void Carrier::print()
{
    std::cout << "Carrier " << id << " with " << clientIds.size() << " clients" << std::endl;
    std::cout << std::endl;
    std::cout << "Clients: " << std::endl;
    for (auto &client : clientIds)
    {
        std::cout << client << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Vehicles: " << std::endl;

    for (auto &vehicle : vehicles)
    {
        vehicle->print();
    }
}

bool Carrier::canAttend(Item *item)
{
    if (clientIds.find(item->clientId) == clientIds.end())
        return false;
    for (auto &vehicle : vehicles)
    {
        if (vehicle->canTake(item))
            return true;
    }
    return false;
}

std::priority_queue<std::pair<double, Vehicle *>> Carrier::getAvailableVehicles(Item *item)
{
    std::priority_queue<std::pair<double, Vehicle *>> availableVehicles;
    for (auto &vehicle : vehicles)
    {
        if (vehicle->canTake(item))
        {
            availableVehicles.push(std::make_pair(calculateTripCostDelta(item, vehicle), vehicle));
        }
    }
    return availableVehicles;
}

double Carrier::calculateTripCostDelta(Item *item, Vehicle *vehicle)
{
    return vehicle->calculateTripCostDelta(item);
}

void Carrier::attendItem(Item *item, Vehicle *vehicle)
{
    vehicle->take(item);
}

void Carrier::reset()
{
    for (auto &vehicle : vehicles)
    {
        vehicle->reset();
    }
}