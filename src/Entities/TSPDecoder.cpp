#include "TSPDecoder.hpp"
#include <cmath>
#include <iostream>

TSPDecoder::TSPDecoder(TSPInstance &_instance) : instance(_instance)
{
}

TSPDecoder::~TSPDecoder()
{
}

BRKGA::fitness_t TSPDecoder::decode(BRKGA::Chromosome &chromosome, bool /* not-used */)
{
	DecodeRooms(chromosome);
	uint fitness = instance.Evaluate(selected_rooms_);
	instance.Reset();
	Reset();
	return fitness;
}

void TSPDecoder::DecodeRooms(BRKGA::Chromosome &chromosome)
{
	for (double allele : chromosome)
	{
		int room = std::floor(allele * instance.room_qtt());
		selected_rooms_.push_back(room);
	}
}
void TSPDecoder::Reset()
{
	selected_rooms_.clear();
}

void TSPDecoder::PrintSolution(BRKGA::Chromosome &chromosome)
{
	DecodeRooms(chromosome);
	uint fitness = instance.Evaluate(selected_rooms_);
	instance.PrintStatistics();
	for (auto &&room : selected_rooms_)
	{
		std::cout << room << std::endl;
	}

	instance.Print();
	std::cout << "Best cost: " << fitness << std::endl;
}