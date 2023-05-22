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
	float PENALTY = 100000000;
	std::vector<Carrier> carriers;
	std::vector<Client> clients;
	std::vector<Item> items;
	std::vector<Vehicle> vehicles;
	std::string testFolder;

	void readAcceptedItemsPerVeichle();
	void readAcceptedClientsPerCarrier();
	void readEntities();
	void addItemsToClients();
	std::vector<std::pair<long double, Vehicle *>> getAvailableVehicles(int itemId);
	void attendItem(Item *itemId, Vehicle *vehicle);
	void createCarriers();
	void sortEntities();
	void setTestFolder();
	std::string addFolder(std::string filename);

public:
	long double fitness = 0;
	TSPInstance();
	~TSPInstance();

	void setUp();
	long double evaluate(std::vector<long double> cromossome);
	uint size();
	void printStatistics();
	void print();
	void attendItem(int itemId, long double vehicleSelector);
	void reset();
	void validate();
	void loadSolution(std::string solution);
};

#endif // __ALLOCATIONHANDLER_H__