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

Item::Item(int id, int clientId, int type, double weight) : id(id),
                                                            clientId(clientId),
                                                            type(type),
                                                            weight(weight)
{
}

Item::~Item()
{
}

void Item::setDestination(Point *p)
{
    destination = *p;
}

double Item::distanceTo(Point *p)
{
    return destination.distanceTo(p);
}