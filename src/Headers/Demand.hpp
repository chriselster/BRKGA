#ifndef __DEMAND_H__
#define __DEMAND_H__
#include "Lecture.hpp"
#include <fstream>
#include <string>
#include <vector>
class Demand
{
private:
	std::string code_;
	uint student_qtt_;
	std::vector<Lecture> lectures_;
	bool allocated = false;
	std::vector<std::string> teachers_;

public:
	Demand();
	Demand(std::ifstream &file);
	~Demand();

	bool operator<(Demand &other);
	void Print();
	uint value();
	std::vector<Lecture> GetLectures();
	uint GetStudentQtt();
	void Allocate();
	bool is_allocated();
};

#endif // __DEMAND_H__