#ifndef __ALLOCATIONHANDLER_H__
#define __ALLOCATIONHANDLER_H__

#include <fstream>
#include <queue>
#include <vector>
#include "Carrier.hpp"
#include "Client.hpp"
#include "Item.hpp"
#include "Vehicle.hpp"
#include "../Entities/CsvReader.cpp"

#include <string>
#include <algorithm>

class TSPInstance
{
private:
	float PENALTY = 1000000;
	std::vector<Carrier> carriers;
	std::vector<Client> clients;
	std::vector<Item> items;
	std::vector<Vehicle> vehicles;

	void readAcceptedItemsPerVeichle();
	void readFaresPerCarrier();
	void readAcceptedClientsPerCarrier();
	void readEntities();
	void addVehiclesToCarriers();
	void addItemsToClients();
	std::vector<std::pair<double, Vehicle *>> getAvailableVehicles(int itemId);
	void attendItem(Item *itemId, Vehicle *vehicle);

public:
	double fitness = 0;
	TSPInstance();
	~TSPInstance();

	void setUp();
	double evaluate(std::vector<double> cromossome);
	uint size();
	void printStatistics();
	void print();
	void attendItem(int itemId, double vehicleSelector);
	void reset();
};

#endif // __ALLOCATIONHANDLER_H__