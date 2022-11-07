#ifndef __LECTURE_H__
#define __LECTURE_H__
#include <fstream>
#include <string>
class Demand;
class Lecture
{
private:
	std::string name_;
	Demand *demand_;
	uint begin_, end_, day_;

public:
	Lecture();
	Lecture(std::ifstream &file);
	~Lecture();

	void Print();
	uint GetBegin();
	uint GetEnd();
	uint GetDay();
	void PrintName();
};

#endif // __LECTURE_H__