
#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"
#include "./Headers/TSPDecoder.hpp"
#include "./Headers/TSPInstance.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

// Rodar 10 vez para cada decoder e instancia variando seed

int main(int argc, char const *argv[])
{

	const unsigned num_generations = std::stoi(argv[1]);

	TSPInstance instance = TSPInstance();
	instance.setUp();
	instance.print();
	int cromossome_size = instance.size();
	if (instance.decoderType == 2)
		cromossome_size *= 2;

	TSPDecoder decoder(instance);
	auto [brkga_params, control_params] =
		BRKGA::readConfiguration("config.conf");
	int seed = std::stoi(argv[2]);

	BRKGA::BRKGA_MP_IPR<TSPDecoder> algorithm(
		decoder, BRKGA::Sense::MINIMIZE, seed,
		cromossome_size, brkga_params);

	const double rho = 0.7;
	algorithm.setBiasCustomFunction([&](const unsigned x)
									{ return x == 1 ? rho : 1.0 - rho; });

	algorithm.initialize();
	algorithm.evolve(1);
	std::cout << "Generation " << 1 << std::endl;
	std::fstream file = std::fstream("../src/output/output.txt", std::ios::out);
	file << "Generation " << 1 << std::endl;
	file.close();
	BRKGA::Chromosome best = algorithm.getBestChromosome();
	decoder.printSolution(best);
	for (unsigned i = 0; i <= num_generations; i += 50)
	{
		algorithm.evolve(50);
		std::cout << "Generation " << i + 50 << std::endl;
		std::fstream file = std::fstream("../src/output/output.txt", std::ios::app);
		file << "Generation " << i + 50 << std::endl
			 << std::endl;
		file.close();
		best = algorithm.getBestChromosome();
		decoder.printSolution(best);
	}

	return 0;
}
