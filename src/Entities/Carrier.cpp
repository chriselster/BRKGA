#include "../Headers/Building.hpp"
#include "../Headers/Log.hpp"
#include <fstream>
#include <iostream>

Building::Building()
{
}

Building::Building(std::ifstream &file)
{
	file >> name_;
	uint days, timeslots, num_rooms;
	file >> days >> timeslots >> num_rooms;
	while (num_rooms--)
	{
		rooms_.push_back(Room(days, timeslots, file));
	}
}

Building::~Building()
{
}

void Building::Print()
{
	Log::GetInstance().Print(name_);
	for (auto room : rooms_)
	{
		room.Print();
	}
}

uint Building::room_qtt()
{
	return rooms_.size();
}

std::vector<Room *> Building::GetRoomPointers()
{
	std::vector<Room *> ptr_rooms;
	for (Room &room : rooms_)
	{
		ptr_rooms.push_back(&room);
	}
	return ptr_rooms;
}