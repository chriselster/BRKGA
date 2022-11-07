#include "../Headers/Timetable.hpp"
#include "Log.hpp"

Slot::Slot() {}
Slot::Slot(Lecture lecture_)
{
	lecture = lecture_;
	empty = false;
}
Timetable::Timetable() {}

Timetable::Timetable(unsigned int days, unsigned int timeslots)
{
	slot_.resize(days);
	for (std::vector<Slot> &day : slot_)
	{
		day.resize(timeslots);
	}
	days_ = days;
	timeslots_ = timeslots;
}

Timetable::~Timetable()
{
}

void Timetable::Print()
{
	for (size_t i = 0; i < timeslots_; i++)
	{
		for (size_t j = 0; j < days_; j++)
		{
			if (!slot_[j][i].empty)
				slot_[j][i].lecture.PrintName();
			Log::GetInstance().PrintSingle(",");
		}
		Log::GetInstance().Print();
	}
}

bool Timetable::CanFit(Demand &demand)
{
	std::vector<Slot *> ptr_slots = GetSlotsUsedBy(demand);
	for (Slot *&ptr_slot : ptr_slots)
	{
		if (!ptr_slot->empty)
			return false;
	}
	return true;
}

void Timetable::Allocate(Demand &demand)
{
	demand.Allocate();
	for (Lecture &lecture : demand.GetLectures())
	{
		for (size_t timeslot = lecture.GetBegin(); timeslot < lecture.GetEnd(); timeslot++)
		{
			Slot new_slot = Slot();
			new_slot.lecture = lecture;
			new_slot.empty = false;
			slot_[lecture.GetDay()][timeslot] = new_slot;
		}
	}
}

std::vector<Slot *> Timetable::GetSlotsUsedBy(Demand demand)
{
	std::vector<Slot *> ptr_slots;
	for (auto &&lecture : demand.GetLectures())
	{
		for (size_t timeslot = lecture.GetBegin(); timeslot < lecture.GetEnd(); timeslot++)
		{
			ptr_slots.push_back(&slot_[lecture.GetDay()][timeslot]);
		}
	}
	return ptr_slots;
}

void Timetable::Reset()
{
	for (std::vector<Slot> &slots : slot_)
	{
		for (Slot &slot : slots)
		{
			slot.empty = true;
		}
	}
}