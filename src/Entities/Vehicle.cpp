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
    capacityLeft = capacity;
}

Vehicle::Vehicle(int id, int carrierId, int type, int capacity)
{
    this->id = id;
    this->carrierId = carrierId;
    this->type = type;
    this->capacity = capacity;
    this->capacityLeft = capacity;
}

Vehicle::~Vehicle()
{
}

void Vehicle::addAcceptedItem(int itemType)
{
    acceptedItems.insert(itemType);
}

bool Vehicle::canTake(Item *item)
{
    if (acceptedItems.find(item->type) == acceptedItems.end())
        return false;

    return capacityLeft >= item->weight;
}

void Vehicle::print()
{
    std::cout << "Vehicle " << id << " of type " << type << " with capacity " << capacity << std::endl;
}
