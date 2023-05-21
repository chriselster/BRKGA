#include "TSPDecoder.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

TSPDecoder::TSPDecoder(TSPInstance &_instance) : instance(_instance)
{
}

TSPDecoder::~TSPDecoder()
{
}

BRKGA::fitness_t TSPDecoder::decode(BRKGA::Chromosome &chromosome, bool /* not-used */)
{
	long double fitness = instance.evaluate(std::vector<long double>(chromosome.begin(), chromosome.end()));
	instance.reset();
	return fitness;
}

void TSPDecoder::printSolution(BRKGA::Chromosome &chromosome)
{
	long double fitness = instance.evaluate(std::vector<long double>(chromosome.begin(), chromosome.end()));
	instance.printStatistics();
	instance.validate();
	std::cout << std::fixed << std::setprecision(8) << "Best cost: " << fitness << std::endl
			  << std::endl;

	std::fstream file = std::fstream("../src/output/output.txt", std::ios::app);
	file << std::fixed << std::setprecision(8) << "Best cost: " << fitness << std::endl
		 << std::endl;
	file.close();
}