#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Item {
public:
    Item(const std::vector<std::string>& values) :
        index(std::stoi(values[0])),
        weight(std::stof(values[1])),
        type(std::stoi(values[2])),
        clientId(std::stoi(values[3]))
    {}

    int index;
    float weight;
    int type;
    int clientId;
};
