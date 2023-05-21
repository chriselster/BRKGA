#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <fstream>
#include <string>
#include <vector>
#include "Item.hpp"

class Client
{
private:
	long double x;
	long double y;
	std::vector<Item *> items;

public:
	int id;
	Client(const std::vector<std::string> &values);
	Client(int id, long double x = 0, long double y = 0);
	~Client();
	void addItem(Item *item);
	void print();
	Point *getPosition();
};

#endif // __CLIENT_H__