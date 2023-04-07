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
	uint fitness = instance.evaluate(std::vector<int>(chromosome.begin(), chromosome.end()));
	return 0;
}

void TSPDecoder::printSolution(BRKGA::Chromosome &chromosome)
{
	uint fitness = instance.evaluate(std::vector<int>(chromosome.begin(), chromosome.end()));
	instance.printStatistics();
	instance.print();
	std::cout << "Best cost: " << fitness << std::endl;
}