#ifndef __ALLOCATIONHANDLER_H__
#define __ALLOCATIONHANDLER_H__

#include "Building.hpp"
#include "Demand.hpp"
#include "Room.hpp"
#include <fstream>
#include <queue>
class TSPInstance
{
private:
	std::vector<Demand> demands_;
	std::vector<Building> buildings_;
	std::vector<Room *> ptr_rooms_;

	void ReadDemands(std::ifstream &file);
	void ReadBuildings(std::ifstream &file);

public:
	TSPInstance();
	~TSPInstance();

	void Print();
	uint Evaluate(std::vector<int> rooms);

	uint room_qtt();
	void Reset();
	uint size();
	void PrintStatistics();
	uint CountAllocatedDemands();
};

#endif // __ALLOCATIONHANDLER_H__