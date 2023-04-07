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
