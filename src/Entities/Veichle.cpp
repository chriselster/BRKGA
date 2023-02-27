#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Vehicle {
public:
    int index;
    double type;
    double capacity;
    int carrierId;

    Vehicle(std::vector<std::string> values) {
        index = std::stoi(values[0]);
        type = std::stod(values[1]);
        capacity = std::stod(values[2]);
        carrierId = std::stoi(values[3]);
    }
};