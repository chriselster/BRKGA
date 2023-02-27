#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



class Carrier {
public:
    Carrier(std::vector<std::string> values) :
        id(std::stoi(values[0])),
        minimumCapacity(std::stof(values[1])),
        costPerAdditionalCustomer(std::stof(values[2])),
        discountPerCapacityIncrease(std::stof(values[3])),
        maxDistanceBetweenCustomers(std::stof(values[4]))
    {}

    int id;
    float minimumCapacity;
    float costPerAdditionalCustomer;
    float discountPerCapacityIncrease;
    float maxDistanceBetweenCustomers;
};

int main() {
    std::vector<Carrier> carriers = CsvReader<Carrier>::from_csv("carriers.csv");

    for (const Carrier& c : carriers) {
        std::cout << "id: " << c.id << ", minimumCapacity: " << c.minimumCapacity
                  << ", costPerAdditionalCustomer: " << c.costPerAdditionalCustomer
                  << ", discountPerCapacityIncrease: " << c.discountPerCapacityIncrease
                  << ", maxDistanceBetweenCustomers: " << c.maxDistanceBetweenCustomers << std::endl;
    }

    return 0;
}
