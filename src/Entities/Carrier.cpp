#include "Carrier.hpp"

Carrier::Carrier(int id) : id(id)
{
    vehicles = std::vector<Vehicle *>();
    clientIds = std::set<int>();
}

Carrier::Carrier()
{
    id = 0;
    vehicles = std::vector<Vehicle *>();
    clientIds = std::set<int>();
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

std::priority_queue<std::pair<long double, Vehicle *>> Carrier::getAvailableVehicles(Item *item)
{
    std::priority_queue<std::pair<long double, Vehicle *>> availableVehicles;
    for (auto &vehicle : vehicles)
    {
        if (vehicle->canTake(item))
        {
            availableVehicles.push(std::make_pair(calculateTripCostDelta(item, vehicle), vehicle));
        }
    }
    return availableVehicles;
}

long double Carrier::calculateTripCostDelta(Item *item, Vehicle *vehicle)
{
    return vehicle->calculateTripCostDelta(item);
}

void Carrier::reset()
{
    for (auto &vehicle : vehicles)
    {
        vehicle->reset();
    }
}

void Carrier::updatePointer(Vehicle *newVehicle)
{
    for (auto &vehicle : vehicles)
    {
        if (vehicle->id == newVehicle->id)
        {
            vehicle = newVehicle;
            return;
        }
    }
}