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
	std::set<int> clientIds;
	Point position = Point(0, 0);

public:
	std::vector<Vehicle *> vehicles;
	int id;
	Carrier(int id);
	Carrier();
	~Carrier();
	void addClient(int clientId);
	void addVehicle(Vehicle *vehicle);
	void print();
	bool canAttend(Item *item);
	std::priority_queue<std::pair<long double, Vehicle *>> getAvailableVehicles(Item *item);
	long double calculateTripCostDelta(Item *item, Vehicle *vehicle);
	void reset();
	void updatePointer(Vehicle *vehicle);
	bool canAttendClient(int clientId);
};

#endif // __Carrier_H__