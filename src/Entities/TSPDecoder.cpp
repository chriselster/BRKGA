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
	double fitness = instance.evaluate(std::vector<double>(chromosome.begin(), chromosome.end()));
	instance.reset();
	return fitness;
}

void TSPDecoder::printSolution(BRKGA::Chromosome &chromosome)
{
	double fitness = instance.evaluate(std::vector<double>(chromosome.begin(), chromosome.end()));
	instance.printStatistics();
	std::cout << std::fixed << std::setprecision(2) << "Best cost: " << fitness << std::endl
			  << std::endl;

	std::fstream file = std::fstream("../src/output/output.txt", std::ios::app);
	file.setf(std::ios::fixed);
	file << "Best cost: " << file.fixed << file.precision(2) << fitness << std::endl
		 << std::endl;
	file.close();
}