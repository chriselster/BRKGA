#include "./Headers/BRKGARunner.hpp"
#include <thread>

// Rodar 10 vez para cada decoder e instancia variando seed

int main(int argc, char const *argv[])
{

	const unsigned num_generations = std::stoi(argv[1]);
	FileGenerator fileGenerator = FileGenerator();
	int seeds[] = {2838, 2139, 6913, 321, 4321, 9876, 12588, 20, 1295, 129482};

	std::thread threads[10];
	for (int i = 0; i < 10; i++)
	{
		std::fstream output = fileGenerator.getOutputFile(seeds[i]);

		TSPInstance instance = TSPInstance();
		instance.setUp();
		instance.print();
		int cromossome_size = instance.size();
		if (instance.decoderType == 2)
			cromossome_size *= 2;

		TSPDecoder decoder(instance);
		auto [brkga_params, control_params] =
			BRKGA::readConfiguration("config.conf");

		BRKGA::BRKGA_MP_IPR<TSPDecoder> algorithm(
			decoder, BRKGA::Sense::MINIMIZE, seeds[i],
			cromossome_size, brkga_params);

		const double rho = 0.7;
		algorithm.setBiasCustomFunction([&](const unsigned x)
										{ return x == 1 ? rho : 1.0 - rho; });

		algorithm.initialize();
		algorithm.evolve(1);
		std::cout << "Generation " << 1 << std::endl;
		output << "Generation " << 1 << std::endl;
		BRKGA::Chromosome best = algorithm.getBestChromosome();
		decoder.printSolution(best, output);
		for (unsigned i = 0; i <= num_generations; i += 50)
		{
			algorithm.evolve(50);
			std::cout << "Generation " << i + 50 << std::endl;
			output << "Generation " << i + 50 << std::endl
				   << std::endl;
			best = algorithm.getBestChromosome();
			decoder.printSolution(best, output);
		}
		output.close();
	}

	// for (int i = 0; i < 10; i++)
	// {
	// 	threads[i].join();
	// }

	return 0;
}
