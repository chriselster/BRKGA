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

	void print();
	uint Evaluate(std::vector<int> rooms);

	void setUp();
	uint room_qtt();
	void Reset();
	uint size();
	void PrintStatistics();
	uint CountAllocatedDemands();
};

#endif // __ALLOCATIONHANDLER_H__