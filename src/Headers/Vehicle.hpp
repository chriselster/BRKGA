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
	std::set<int> acceptedItems;

public:
	double remainingCapacity;
	int carrierId;
	int id;
	int type;
	Vehicle(std::vector<std::string> values);
	Vehicle(int id, int carrierId, int type, double capacity);
	~Vehicle();
	void addAcceptedItem(int itemType);
	bool canTake(Item *itemType);
	void print();
	void take(Item *item);
};

#endif // __Vehicle_H__