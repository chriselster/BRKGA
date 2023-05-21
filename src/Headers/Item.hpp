#ifndef ITEM_HPP
#define ITEM_HPP
#include "Point.hpp"
class Vehicle;

class Item
{
private:
	bool attended = false;

public:
	Vehicle *vehicle = nullptr;
	Point destination;
	long double weight;
	int type;
	int clientId;
	int id;
	Item(const std::vector<std::string> &values);
	Item(int id, int clientId, int type, long double weight);
	~Item();
	void setVehicle(Vehicle *vehicle);
	void setDestination(Point *point);
	long double distanceTo(Point *point);
	void setWeight(long double weight);
	bool wasAttended();
	void reset();
};

#endif // ITEM_HPP