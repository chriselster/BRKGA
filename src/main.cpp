#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"

#include "./Headers/BRKGARunner.hpp"
#include "./Headers/RunArguments.hpp"
#include "./Headers/TSPInstance.hpp"
#include "./Headers/TSPDecoder.hpp"

#include <thread>

// Rodar 10 vez para cada decoder e instancia variando seed

void run(RunArguments args)
{
	FileGenerator fileGenerator = FileGenerator();
	std::fstream output = fileGenerator.getOutputFile(args.output_file_location);

	TSPInstance instance = TSPInstance(args);
	instance.setUp();
	instance.print();
	int cromossome_size = instance.size();
	if (args.decoderType == 2)
		cromossome_size *= 2;

	TSPDecoder decoder(instance);
	auto [brkga_params, control_params] =
		BRKGA::readConfiguration("config.conf");

	BRKGA::BRKGA_MP_IPR<TSPDecoder> algorithm(
		decoder, BRKGA::Sense::MINIMIZE, args.seed,
		cromossome_size, brkga_params);

	const double rho = 0.7;
	algorithm.setBiasCustomFunction([&](const unsigned x)
									{ return x == 1 ? rho : 1.0 - rho; });

	algorithm.initialize();
	algorithm.evolve(1);
	output << "Generation " << 1 << std::endl;
	BRKGA::Chromosome best = algorithm.getBestChromosome();
	decoder.printSolution(best, output);
	for (unsigned i = 0; i <= args.number_of_generations; i += 50)
	{
		algorithm.evolve(50);
		output << "Generation " << i + 50 << std::endl;
		best = algorithm.getBestChromosome();
		decoder.printSolution(best, output);
	}
	output.close();
}

int main(int argc, char const *argv[])
{

	RunArguments args(argv);
	run(args);

	return 0;
}
