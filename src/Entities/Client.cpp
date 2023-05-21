#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Client.hpp"

Client::Client(const std::vector<std::string> &values) : id(std::stoi(values[0])),
                                                         x(std::stof(values[1])),
                                                         y(std::stof(values[2]))
{
}

Client::Client(int id, long double x, long double y) : id(id),
                                             x(x),
                                             y(y)
{
}

Client::~Client()
{
}

void Client::print()
{
    std::cout << "Client " << id << " at (" << x << ", " << y << ")" << std::endl;
}

void Client::addItem(Item *item)
{
    items.push_back(item);
}

Point *Client::getPosition()
{
    return new Point(x, y);
}