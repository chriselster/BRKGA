
#include "brkga_mp_ipr/brkga_mp_ipr.hpp"
#include "TSPDecoder.hpp"
#include "TSPInstance.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
	const unsigned num_generations = std::stoi(argv[1]);

	TSPInstance instance = TSPInstance();

	TSPDecoder decoder(instance);

	auto [brkga_params, control_params] =
		BRKGA::readConfiguration("config.conf");

	BRKGA::BRKGA_MP_IPR<TSPDecoder> algorithm(
		decoder, BRKGA::Sense::MAXIMIZE, 0,
		instance.size(), brkga_params);

	algorithm.initialize();

	algorithm.evolve(num_generations);

	BRKGA::Chromosome best = algorithm.getBestChromosome();
	decoder.PrintSolution(best);

	return 0;
}