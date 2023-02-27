#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Fare {
public:
    Fare(const std::vector<std::string>& values) :
        vehicleType(std::stoi(values[0])),
        fare(std::stof(values[1])),
        carrierId(std::stoi(values[2]))
    {}

    int vehicleType;
    float fare;
    int carrierId;
};
