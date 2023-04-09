#ifndef __Carrier_H__
#define __Carrier_H__
#include "Client.hpp"
#include "Vehicle.hpp"
#include "Point.hpp"
#include "Item.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <queue>
#include <utility>
#include <map>
class Carrier
{
private:
	// Capacity below which the carrier will apply a fare
	float minimumCapacity;
	// Cost per additional customer
	float costPerAdditionalCustomer;
	// TODO: perguntar pro Rafa
	float discountPerCapacityIncrease;
	// Maximum distance for a client to be able to be served in the same vehicle
	// Fare per vehicle type per Km
	std::vector<double> farePerVehicleTypePerKm;
	std::vector<Vehicle *> vehicles;
	std::set<int> clientIds;
	Point position = Point(0, 0);
	std::map<int, std::vector<Vehicle *>> proximityClients;

public:
	float maxDistanceBetweenClients;
	int id;
	Carrier(std::vector<std::string> values);
	Carrier(float minimumCapacity, float costPerAdditionalCustomer, float discountPerCapacityIncrease, float maxDistanceBetweenCustomers);
	Carrier();
	~Carrier();
	void addClient(int clientId);
	void addVehicle(Vehicle *vehicle);
	void addFare(int vehicleType, double fare);
	void print();
	bool canAttend(Item *item);
	std::priority_queue<std::pair<double, Vehicle *>> getAvailableVehicles(Item *item);
	double calculateTripCost(Item *item, Vehicle *vehicle);
	void attendItem(Item *item, Vehicle *vehicle);
	void addProximityClient(int clientId, Vehicle *vehicle);
};

#endif // __Carrier_H__