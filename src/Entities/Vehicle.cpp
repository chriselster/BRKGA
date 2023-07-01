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
    type = std::stoi(values[1]);
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
    item->setVehicle(this);
    addToVehicle(item);
}

void Vehicle::addToVehicle(Item *item)
{
    remainingCapacity -= item->weight;
    items.insert(item);
    if (alreadyVisited(item->clientId))
        return;
    visitedClients.insert(item->clientId);
    visitedPoints.insert(&item->destination);
}

void Vehicle::removeFromVehicle(Item *item, bool clientWasAlreadtyVisited)
{
    remainingCapacity += item->weight;
    items.erase(item);
    if (clientWasAlreadtyVisited)
        return;
    visitedClients.erase(item->clientId);
    visitedPoints.erase(&item->destination);
}

void Vehicle::reset()
{
    remainingCapacity = capacity;
    visitedClients.clear();
    visitedPoints.clear();
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
    return calculateTripCostWhenTaking(item) - tripCost();
}

long double Vehicle::calculateTripCostWhenTaking(Item *item)
{
    bool clientWasAlreadtyVisited = alreadyVisited(item->clientId);
    addToVehicle(item);
    long double cost = tripCost();
    removeFromVehicle(item, clientWasAlreadtyVisited);
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

long double Vehicle::tripCost()
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

bool Vehicle::canVisitAllClients()
{

    for (Point *visitedPoint : visitedPoints)
    {
        bool ok = false;
        for (Point *otherPoint : visitedPoints)
        {
            if (visitedPoint->distanceTo(otherPoint) <= maxDistanceBetweenClients)
            {
                ok = true;
                break;
            }
        }
        if (!ok)
            return false;
    }
    return true;
}

bool Vehicle::hasIncorrectPoints()
{
    bool ok =
        visitedClients.size() == visitedPoints.size();
    std::set<int> visitedClientsSet;
    for (auto item : items)
    {
        visitedClientsSet.insert(item->clientId);
    }
    ok = ok && visitedClientsSet.size() == visitedClients.size();
    return !ok;
}

bool Vehicle::canTakeAllItems()
{
    long double totalWeight = 0;
    for (Item *item : items)
    {
        if (acceptedItemTypes.find(item->type) == acceptedItemTypes.end())
            return false;
        totalWeight += item->weight;
    }
    return totalWeight <= capacity;
}