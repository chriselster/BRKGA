#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Vehicle.hpp"

Vehicle::Vehicle(std::vector<std::string> values)
{
    id = std::stoi(values[0]);
    type = std::stod(values[1]);
    capacity = std::stod(values[2]);
    carrierId = std::stoi(values[3]);
    remainingCapacity = capacity;
}

Vehicle::Vehicle(int id, int carrierId, int type, double capacity)
{
    this->id = id;
    this->carrierId = carrierId;
    this->type = type;
    this->capacity = capacity;
    this->remainingCapacity = capacity;
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
}

void Vehicle::reset()
{
    remainingCapacity = capacity;
}