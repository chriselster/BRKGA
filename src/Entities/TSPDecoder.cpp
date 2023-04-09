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
	uint fitness = instance.evaluate(std::vector<double>(chromosome.begin(), chromosome.end()));
	return fitness;
}

void TSPDecoder::printSolution(BRKGA::Chromosome &chromosome)
{
	uint fitness = instance.evaluate(std::vector<double>(chromosome.begin(), chromosome.end()));
	instance.printStatistics();
	std::cout << "Best cost: " << fitness << std::endl;
}