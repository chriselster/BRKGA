#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <fstream>
#include <string>
#include <vector>

class Client
{
private:
	double x;
	double y;

public:
	int id;
	Client(const std::vector<std::string> &values);
	~Client();
};

#endif // __CLIENT_H__