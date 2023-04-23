#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Vehicle.hpp"
#include "Item.hpp"

Vehicle::Vehicle(std::vector<std::string> values)
{
    id = std::stoi(values[0]);
    carrierId = std::stoi(values[1]);
    type = std::stod(values[2]);
    capacity = std::stod(values[3]);
    costPerKmPerWeight = std::stod(values[4]);
    minimumContractedLoad = std::stod(values[5]);
    additionalForMultipleClients = std::stod(values[6]);
    maxDistanceBetweenClients = std::stod(values[7]);
    remainingCapacity = capacity;
}

Vehicle::Vehicle(int id, int carrierId, int type, double capacity, double costPerKm, double minimumCapacity, double additionalForMultipleClients)
{
    this->id = id;
    this->carrierId = carrierId;
    this->type = type;
    this->capacity = capacity;
    this->remainingCapacity = capacity;
    this->costPerKmPerWeight = costPerKm;
    this->minimumContractedLoad = minimumCapacity;
    this->additionalForMultipleClients = additionalForMultipleClients;
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
    currentTripCost = calculateTripCost(item);
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
    return calculateTripCost(item) - currentTripCost;
}

double Vehicle::calculateTripCost(Item *item)
{
    double cost = 0;
    if (alreadyVisited(item->clientId))
        return 0;
    if (visitedClients.size() > 0)
        cost += additionalForMultipleClients;
    cost += calculateDeadFreightCost(item);
    cost += costPerKmPerWeight * origin.distanceTo(&item->destination) * item->weight;
    return cost;
}

void Vehicle::setMinimumCapacity(double minimumCapacity)
{
    this->minimumContractedLoad = minimumCapacity;
}

double Vehicle::getFarthestDistance(Point *point)
{
    double fartherDistance = origin.distanceTo(point);
    for (Point *visitedPoint : visitedPoints)
    {
        double distance = visitedPoint->distanceTo(point);
        if (distance > fartherDistance)
            fartherDistance = distance;
    }
    return fartherDistance;
}

double Vehicle::calculateDeadFreightCost(Item *item)
{
    double cost = 0;
    double newUsedCapacity = usedCapacity() + item->weight;
    if (newUsedCapacity < minimumContractedLoad)
    {
        double fartherstDistance = getFarthestDistance(&item->destination);
        cost += fartherstDistance * costPerKmPerWeight * std::max(minimumContractedLoad - newUsedCapacity, 0.0);
    }
    return cost;
}