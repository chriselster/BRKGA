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

public:
	TSPInstance();
	~TSPInstance();

	void setUp();
	uint evaluate(std::vector<int> cromossome);
	uint size();
	void printStatistics();
	void print();
};

#endif // __ALLOCATIONHANDLER_H__