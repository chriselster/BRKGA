#ifndef __FARES_H__
#define __FARES_H__
#include <vector>

class Fares
{
private:
	std::vector<double> typeValues;

public:
	Fares(const std::vector<std::string> &values);
	~Fares();
};

#endif // __FARES_H__