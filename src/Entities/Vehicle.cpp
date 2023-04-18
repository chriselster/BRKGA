#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Vehicle.hpp"
#include "Item.hpp"
#include "PathOptimizer.hpp"

Vehicle::Vehicle(std::vector<std::string> values)
{
    id = std::stoi(values[0]);
    type = std::stod(values[1]);
    capacity = std::stod(values[2]);
    carrierId = std::stoi(values[3]);
    costPerKm = std::stod(values[4]);
    remainingCapacity = capacity;
}

Vehicle::Vehicle(int id, int carrierId, int type, double capacity, double costPerKm)
{
    this->id = id;
    this->carrierId = carrierId;
    this->type = type;
    this->capacity = capacity;
    this->remainingCapacity = capacity;
    this->costPerKm = costPerKm;
}

Vehicle::~Vehicle()
{
}

void Vehicle::addAcceptedItem(int itemType)
{
    acceptedItemTypes.insert(itemType);
}

bool Vehicle::canTake(Item *item)
{
    if (acceptedItemTypes.find(item->type) == acceptedItemTypes.end())
        return false;

    return remainingCapacity >= item->weight;
}

void Vehicle::print()
{
    std::cout << "Vehicle " << id << " of type " << type << " with capacity " << capacity << std::endl;
}

void Vehicle::take(Item *item)
{
    item->setVehicle(this);
    remainingCapacity -= item->weight;
    if (alreadyVisited(item->clientId))
        return;
    visitedClients.insert(item->clientId);
    visitedPoints.push_back(&item->destination);
    // TODO: da pra utilizar como atributo
    PathOptimizer pathOptimizer = PathOptimizer(visitedPoints);
    currentTripCost = pathOptimizer.getShortestPath() * costPerKm;
}

void Vehicle::reset()
{
    remainingCapacity = capacity;
}

double Vehicle::usedCapacity()
{
    return capacity - remainingCapacity;
}

bool Vehicle::alreadyVisited(int clientId)
{
    return visitedClients.find(clientId) != visitedClients.end();
}

double Vehicle::calculateTripCostDelta(Item *item)
{
    double cost = 0;
    if (alreadyVisited(item->clientId))
    {
        return 0;
    }
    PathOptimizer pathOptimizer = PathOptimizer(visitedPoints);
    pathOptimizer.addPoint(&item->destination);
    cost = pathOptimizer.getShortestPath() * costPerKm;
    return cost - currentTripCost;
}
