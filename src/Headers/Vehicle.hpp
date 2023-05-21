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
	long double capacity;
	long double minimumContractedLoad;
	long double maxDistanceBetweenClients;
	long double additionalForMultipleClients;
	std::set<int> acceptedItemTypes;
	std::set<int> visitedClients;
	std::set<Point *> visitedPoints;
	std::set<Item *> items;
	long double currentTripCost = 0;
	long double currentTripDeadFreightCost = 0;
	Point origin = Point(0, 0);
	long double calculateTripCostWhenTaking(Item *item);
	void updateCurrentTripInfo(Item *item);
	long double getFarthestTrip();
	long double calculateDeadFreightCostWhenTaking(Item *item);
	long double calculateDeadFreight();
	long double baseTripCost(Item *item);
	void addToVehicle(Item *item);
	void removeFromVehicle(Item *item, bool clientWasAlreadyVisited);
	long double costPerKmPerWeight;

public:
	long double remainingCapacity;
	int carrierId;
	int id;
	int type;
	Vehicle(std::vector<std::string> values);
	Vehicle(int id, int carrierId, int type, long double capacity, long double costPerKm,
			long double minimumCapacity, long double additionalForMultipleClients, long double maxDistanceBetweenClients);
	~Vehicle();
	void addAcceptedItem(int itemType);
	bool canTake(Item *itemType);
	void print();
	void take(Item *item);
	void reset();
	long double tripCost();
	long double usedCapacity();
	bool alreadyVisited(int clientId);
	long double calculateTripCostDelta(Item *item);
	void setMinimumCapacity(long double minimumCapacity);
	bool canVisitAllClients();
	bool hasIncorrectPoints();
};

#endif // __Vehicle_H__