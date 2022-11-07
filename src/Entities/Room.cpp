#include "../Headers/Room.hpp"
#include "../Headers/Log.hpp"
#include <iostream>

Room::Room(unsigned int days, unsigned int timeslots, std::ifstream &file)
{
	file >> number_ >> capacity_;
	timetable_ = Timetable(days, timeslots);
}

Room::~Room()
{
}

void Room::Print()
{
	Log::GetInstance().Print(number_);
	timetable_.Print();
}

bool Room::Allocate(Demand &demand)
{
	if (demand.GetStudentQtt() > capacity_)
		return false;
	if (timetable_.CanFit(demand))
	{
		timetable_.Allocate(demand);
		return true;
	}
	return false;
}

void Room::Reset()
{
	timetable_.Reset();
}