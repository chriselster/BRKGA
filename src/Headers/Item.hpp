#ifndef __LOG_H__
#define __LOG_H__

class Item
{
private:
	double weight;
	int type;

public:
	int clientId;
	int id;
	Item(const std::vector<std::string> &values);
	~Item();
};

#endif // __LOG_H__