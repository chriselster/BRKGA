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
}

Vehicle::~Vehicle()
{
}

void Vehicle::addAcceptedItem(int itemType)
{
    acceptedItems.push_back(itemType);
}

bool Vehicle::acceptsItem(int itemType)
{
    for (int i = 0; i < acceptedItems.size(); i++)
    {
        if (acceptedItems[i] == itemType)
        {
            return true;
        }
    }
    return false;
}

void Vehicle::print()
{
    std::cout << "Vehicle " << id << " of type " << type << " with capacity " << capacity << std::endl;
}
