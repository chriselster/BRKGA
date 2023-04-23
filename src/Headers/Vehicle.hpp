#ifndef __Vehicle_H__
#define __Vehicle_H__
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include "Item.hpp"
#include "Point.hpp"
class Vehicle
{
private:
	double capacity;
	double minimumContractedLoad;
	double maxDistanceBetweenClients;
	double additionalForMultipleClients;
	std::set<int> acceptedItemTypes;
	std::set<int> visitedClients;
	std::vector<Point *> visitedPoints;
	double currentTripCost = 0;
	Point origin = Point(0, 0);
	double calculateTripCost(Item *item);
	double getFarthestDistance(Point *point);
	double calculateDeadFreightCost(Item *item);
	double costPerKmPerWeight;

public:
	double remainingCapacity;
	int carrierId;
	int id;
	int type;
	Vehicle(std::vector<std::string> values);
	Vehicle(int id, int carrierId, int type, double capacity, double costPerKm,
			double minimumCapacity, double additionalForMultipleClients, double maxDistanceBetweenClients);
	~Vehicle();
	void addAcceptedItem(int itemType);
	bool canTake(Item *itemType);
	void print();
	void take(Item *item);
	void reset();
	double usedCapacity();
	bool alreadyVisited(int clientId);
	double calculateTripCostDelta(Item *item);
	void setMinimumCapacity(double minimumCapacity);
};

#endif // __Vehicle_H__