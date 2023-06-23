#include "TSPDecoder.hpp"

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

void TSPDecoder::printSolution(BRKGA::Chromosome &chromosome, std::fstream &file)
{
	long double fitness = instance.evaluate(std::vector<long double>(chromosome.begin(), chromosome.end()));
	instance.printStatistics(file);
	instance.validate();
	std::cout << std::fixed << std::setprecision(8) << "Best cost: " << fitness << std::endl
			  << std::endl;

	file << std::fixed << std::setprecision(8) << "Best cost: " << fitness << std::endl
		 << std::endl;
}