#ifndef __Carrier_H__
#define __Carrier_H__
#include "Room.hpp"
#include <fstream>
#include <string>
#include <vector>

class Carrier
{
private:
	bool quadrants[4];
	double baseFarePerType[3];
	double minimumCapacity;
	double costPerAdditionalCustomer;
	double discoutPerCapacityIncrease;
	double maxDistanceBetweenCustomers;

public:
	Carrier();
	Carrier(std::ifstream &file);
	~Carrier();
	void Print();

	uint room_qtt();
	std::vector<Room *> GetRoomPointers();
};

#endif // __Carrier_H__