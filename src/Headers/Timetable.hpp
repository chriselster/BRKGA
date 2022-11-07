#ifndef __TIMETABLE_H__
#define __TIMETABLE_H__
#include "Demand.hpp"
#include "Lecture.hpp"
#include <vector>

class Slot
{
public:
	Slot();
	Slot(Lecture lecture_);

	Lecture lecture;
	bool empty = true;
};

class Timetable
{
private:
	std::vector<std::vector<Slot>> slot_;
	uint days_, timeslots_;

public:
	Timetable();
	Timetable(unsigned int days, unsigned int timeslots);
	~Timetable();

	bool CanFit(Demand &demand);
	void Allocate(Demand &demand);
	void Print();

	std::vector<Slot *> GetSlotsUsedBy(Demand demand);
	void Reset();
};

#endif // __TIMETABLE_H__