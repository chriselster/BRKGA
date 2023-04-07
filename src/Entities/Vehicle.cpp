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

void Vehicle::addAcceptedItem(int itemType)
{
    acceptedItems.push_back(itemType);
}