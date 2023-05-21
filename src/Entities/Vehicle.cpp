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
    type = std::stod(values[1]);
    capacity = std::stod(values[2]);
    carrierId = std::stoi(values[3]);
    minimumContractedLoad = std::stod(values[4]);
    costPerKmPerWeight = std::stod(values[5]);
    additionalForMultipleClients = std::stod(values[6]);
    maxDistanceBetweenClients = std::stod(values[7]);
    remainingCapacity = capacity;
}

Vehicle::Vehicle(int id, int carrierId, int type, long double capacity, long double costPerKm, long double minimumCapacity, long double additionalForMultipleClients, long double maxDistanceBetweenClients)
{
    this->id = id;
    this->carrierId = carrierId;
    this->type = type;
    this->capacity = capacity;
    this->remainingCapacity = capacity;
    this->costPerKmPerWeight = costPerKm;
    this->minimumContractedLoad = minimumCapacity;
    this->additionalForMultipleClients = additionalForMultipleClients;
    this->maxDistanceBetweenClients = maxDistanceBetweenClients;
    remainingCapacity = capacity;
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

    if (remainingCapacity < item->weight)
        return false;

    if (visitedPoints.size() > 0)
    {
        for (Point *visitedPoint : visitedPoints)
        {
            if (visitedPoint->distanceTo(&item->destination) <= maxDistanceBetweenClients)
                return true;
        }
        return false;
    }

    return true;
}

void Vehicle::print()
{
    std::cout << "Vehicle " << id << " of type " << type << " with capacity " << capacity << std::endl;
}

void Vehicle::take(Item *item)
{
    updateCurrentTripInfo(item);
    item->setVehicle(this);
    addToVehicle(item);
}

void Vehicle::addToVehicle(Item *item)
{
    remainingCapacity -= item->weight;
    items.push_back(item);
    if (alreadyVisited(item->clientId))
        return;
    visitedClients.insert(item->clientId);
    visitedPoints.push_back(&item->destination);
}

void Vehicle::updateCurrentTripInfo(Item *item)
{
    currentTripCost = calculateTripCost(item);
    currentTripDeadFreightCost = calculateDeadFreightCostWhenTaking(item);
}

void Vehicle::reset()
{
    remainingCapacity = capacity;
    visitedClients.clear();
    visitedPoints.clear();
    currentTripCost = 0;
    currentTripDeadFreightCost = 0;
    items.clear();
}

long double Vehicle::usedCapacity()
{
    return capacity - remainingCapacity;
}

bool Vehicle::alreadyVisited(int clientId)
{
    return visitedClients.find(clientId) != visitedClients.end();
}

long double Vehicle::calculateTripCostDelta(Item *item)
{
    return calculateTripCost(item) - currentTripCost;
}

long double Vehicle::calculateTripCost(Item *item)
{
    long double cost = 0;
    if (visitedClients.size() == 1 && !alreadyVisited(item->clientId))
        cost += additionalForMultipleClients;
    cost += currentTripCost - currentTripDeadFreightCost;
    cost += calculateDeadFreightCostWhenTaking(item);
    cost += baseTripCost(item);
    return cost;
}

long double Vehicle::baseTripCost(Item *item)
{
    return costPerKmPerWeight * origin.distanceTo(&item->destination) * item->weight;
}

void Vehicle::setMinimumCapacity(long double minimumCapacity)
{
    this->minimumContractedLoad = minimumCapacity;
}

long double Vehicle::getFarthestTrip()
{
    long double fartherDistance = 0;
    for (Point *visitedPoint : visitedPoints)
    {
        long double distance = origin.distanceTo(visitedPoint);
        if (distance > fartherDistance)
            fartherDistance = distance;
    }
    return fartherDistance;
}

long double Vehicle::calculateDeadFreightCostWhenTaking(Item *item)
{
    addToVehicle(item);
    long double cost = calculateDeadFreight();
    removeFromVehicle(item);
    return cost;
}

void Vehicle::removeFromVehicle(Item *item)
{
    remainingCapacity += item->weight;
    visitedClients.erase(item->clientId);
    visitedPoints.pop_back();
    items.pop_back();
}

long double Vehicle::calculateDeadFreight()
{
    long double cost = 0;
    long double totalUsedCapacity = usedCapacity();
    if (totalUsedCapacity < minimumContractedLoad)
    {
        cost += getFarthestTrip() * costPerKmPerWeight * std::max(minimumContractedLoad - totalUsedCapacity, 0.0L);
    }
    return cost;
}

long double Vehicle::totalCost()
{
    long double cost = 0;
    if (visitedClients.size() > 1)
        cost += additionalForMultipleClients;
    for (Item *item : items)
    {
        cost += baseTripCost(item);
    }
    cost += calculateDeadFreight();
    return cost;
}