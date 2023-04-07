#ifndef __Carrier_H__
#define __Carrier_H__
#include "Client.hpp"
#include "Vehicle.hpp"
#include <vector>
#include <string>
#include <iostream>
class Carrier
{
private:
	float minimumCapacity;
	float costPerAdditionalCustomer;
	float discountPerCapacityIncrease;
	float maxDistanceBetweenCustomers;
	std::vector<double> farePerVehicleType;
	std::vector<Client *> clients;
	std::vector<Vehicle *> vehicles;

public:
	int id;
	Carrier(std::vector<std::string> values);
	~Carrier();
	void addClient(Client *client);
	void addVehicle(Vehicle *vehicle);
	void addFare(int vehicleType, double fare);
	void print();
};

#endif // __Carrier_H__