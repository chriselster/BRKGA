#ifndef ITEM_HPP
#define ITEM_HPP
#include "Point.hpp"

class Item
{
private:
public:
	Point destination;
	double weight;
	int type;
	int clientId;
	int id;
	Item(const std::vector<std::string> &values);
	Item(int id, int clientId, int type, double weight);
	~Item();
	void setDestination(Point *p);
	double distanceTo(Point *p);
};

#endif // ITEM_HPP