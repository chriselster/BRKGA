#ifndef __Vehicle_H__
#define __Vehicle_H__
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include "Item.hpp"
class Vehicle
{
private:
	double capacity;
	std::set<int> acceptedItemTypes;
	std::set<int> visitedClients;
	std::vector<Point *> visitedPoints;
	double currentTripCost = 0;

public:
	double costPerKm;
	double remainingCapacity;
	int carrierId;
	int id;
	int type;
	Vehicle(std::vector<std::string> values);
	Vehicle(int id, int carrierId, int type, double capacity, double costPerKm);
	~Vehicle();
	void addAcceptedItem(int itemType);
	bool canTake(Item *itemType);
	void print();
	void take(Item *item);
	void reset();
	double usedCapacity();
	bool alreadyVisited(int clientId);
	double calculateTripCostDelta(Item *item);
};

#endif // __Vehicle_H__