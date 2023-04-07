#ifndef __Vehicle_H__
#define __Vehicle_H__

class Vehicle
{
private:
	int capacity;
	std::vector<int> acceptedItems;

public:
	int carrierId;
	int id;
	int type;
	Vehicle(std::vector<std::string> values);
	~Vehicle();
	void addAcceptedItem(int itemType);
	bool acceptsItem(int itemType);
	void print();
};

#endif // __Vehicle_H__