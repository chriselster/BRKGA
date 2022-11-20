#ifndef __Carrier_H__
#define __Carrier_H__
#include "Fares.hpp"
#include "Quadrant.hpp"

class Carrier
{
private:
	Quadrants quadrants;
	Fares fare;
	double minimumCapacity;
	double costPerAdditionalCustomer;
	double discoutPerCapacityIncrease;
	double maxDistanceBetweenCustomers;

public:
	Carrier();
	~Carrier();
};

#endif // __Carrier_H__