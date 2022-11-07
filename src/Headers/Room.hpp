#ifndef __ROOM_H__
#define __ROOM_H__
#include "Demand.hpp"
#include "Timetable.hpp"
#include <fstream>
class Room
{
private:
	int number_;
	uint capacity_;
	Timetable timetable_;

public:
	Room(unsigned int days, unsigned int timeslots, std::ifstream &file);
	~Room();

	void Print();
	bool Allocate(Demand &demand);
	void Reset();
};

#endif // __ROOM_H__