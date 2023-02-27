#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Client {
public:
    Client(const std::vector<std::string>& values) :
        index(std::stoi(values[0])),
        X_coordinate(std::stof(values[1])),
        Y_coordinate(std::stof(values[2]))
    {}

    int index;
    float X_coordinate;
    float Y_coordinate;
};
