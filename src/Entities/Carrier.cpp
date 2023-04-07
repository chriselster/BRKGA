#include "Carrier.hpp"

Carrier::Carrier(std::vector<std::string> values) : id(std::stoi(values[0])),
                                                    minimumCapacity(std::stof(values[1])),
                                                    costPerAdditionalCustomer(std::stof(values[2])),
                                                    discountPerCapacityIncrease(std::stof(values[3])),
                                                    maxDistanceBetweenCustomers(std::stof(values[4]))
{
}

void Carrier::addClient(Client *client)
{
    clients.push_back(client);
}

void Carrier::addFare(int vehicleType, double fare)
{
    farePerVehicleType[vehicleType] = fare;
}

void Carrier::addVehicle(Vehicle *vehicle)
{
    vehicles.push_back(vehicle);
}

void Carrier::print()
{
    std::cout << "Carrier " << id << " with " << clients.size() << " clients" << std::endl;
    std::cout << std::endl;
    std::cout << "Clients: " << std::endl;
    for (auto &client : clients)
    {
        client->print();
    }
    std::cout << std::endl;
    std::cout << "Vehicles: " << std::endl;

    for (auto &vehicle : vehicles)
    {
        vehicle->print();
    }
}