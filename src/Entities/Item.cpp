#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Item.hpp"

Item::Item(const std::vector<std::string> &values) : id(std::stoi(values[0])),
                                                     weight(std::stof(values[1])),
                                                     type(std::stoi(values[2])),
                                                     clientId(std::stoi(values[3]))
{
}

Item::~Item()
{
}