#include "TSPInstance.hpp"
#include "Log.hpp"
#include <algorithm>
#include <vector>
TSPInstance::TSPInstance()
{
	std::ifstream file = std::ifstream("in.txt");
	ReadBuildings(file);
	ReadDemands(file);
}

TSPInstance::~TSPInstance()
{
}

void TSPInstance::ReadBuildings(std::ifstream &file)
{
	uint num_buildings;
	file >> num_buildings;
	for (size_t i = 0; i < num_buildings; i++)
	{
		Building building = Building(file);
		buildings_.push_back(building);
		std::vector<Room *> ptr_rooms = buildings_.back().GetRoomPointers();
		ptr_rooms_.insert(ptr_rooms_.begin(), ptr_rooms.begin(), ptr_rooms.end());
	}
}

uint TSPInstance::size()
{
	return demands_.size();
}

void TSPInstance::ReadDemands(std::ifstream &file)
{
	while (!file.eof())
	{
		Demand demand = Demand(file);
		demands_.push_back(demand);
	}
	std::sort(demands_.begin(), demands_.end());
}

void TSPInstance::Print()
{
	for (auto &&building : buildings_)
	{
		building.Print();
	}
}

uint TSPInstance::Evaluate(std::vector<int> selected_rooms)
{
	uint index = 0;
	uint fittness = 0;
	for (Demand &demand : demands_)
	{
		if (ptr_rooms_[selected_rooms[index++]]->Allocate(demand))
			fittness += demand.value();
	}
	return fittness;
}

uint TSPInstance::room_qtt()
{
	uint total = 0;
	for (Building &building : buildings_)
	{
		total += building.room_qtt();
	}
	return total;
}

void TSPInstance::Reset()
{
	for (Room *&ptr_room : ptr_rooms_)
	{
		ptr_room->Reset();
	}
}

void TSPInstance::PrintStatistics()
{
	uint allocated_demands = CountAllocatedDemands();
	Log::GetInstance().Print("Alocadas:", allocated_demands, demands_.size());
}

uint TSPInstance::CountAllocatedDemands()
{
	uint allocated_demands = 0;
	for (auto &&demand : demands_)
	{
		if (demand.is_allocated())
			allocated_demands++;
	}
	return allocated_demands;
}