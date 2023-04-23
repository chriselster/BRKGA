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
	double weight;
	int type;
	int clientId;
	int id;
	Item(const std::vector<std::string> &values);
	Item(int id, int clientId, int type, double weight);
	~Item();
	void setVehicle(Vehicle *vehicle);
	void setDestination(Point *point);
	double distanceTo(Point *point);
	void setWeight(double weight);
	bool wasAttended();
};

#endif // ITEM_HPP