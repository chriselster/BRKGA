#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <fstream>
#include <string>
#include <vector>

class Client
{
private:
	int id;
	double x;
	double y;

public:
	Client();
	~Client();
};

#endif // __CLIENT_H__