
#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"
#include "./Headers/TSPDecoder.hpp"
#include "./Headers/TSPInstance.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{

	const unsigned num_generations = std::stoi(argv[1]);

	TSPInstance instance = TSPInstance();
	instance.setUp();
	instance.print();

	TSPDecoder decoder(instance);
	auto [brkga_params, control_params] =
		BRKGA::readConfiguration("config.conf");

	BRKGA::BRKGA_MP_IPR<TSPDecoder> algorithm(
		decoder, BRKGA::Sense::MINIMIZE, 0,
		instance.size(), brkga_params);

	algorithm.initialize();

	algorithm.evolve(num_generations);

	BRKGA::Chromosome best = algorithm.getBestChromosome();
	decoder.printSolution(best);

	return 0;
}
