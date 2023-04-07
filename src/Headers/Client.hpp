#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <fstream>
#include <string>
#include <vector>
#include "Item.hpp"

class Client
{
private:
	double x;
	double y;
	std::vector<Item *> items;

public:
	int id;
	Client(const std::vector<std::string> &values);
	~Client();
	void addItem(Item *item);
	void print();
};

#endif // __CLIENT_H__