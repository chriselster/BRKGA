#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"

#include "./Headers/FileGenerator.hpp"
#include "./Headers/RunArguments.hpp"
#include "./Headers/TSPInstance.hpp"
#include "./Headers/TSPDecoder.hpp"
#include <chrono>

using namespace chrono;
using namespace std;

//-------------------------[ Simple logging function ]------------------------//

void log(const string &message, ostream &output = cout)
{
	auto start_time = system_clock::to_time_t(system_clock::now());
	string ss(ctime(&start_time));
	ss.pop_back(); // Workaround to skip unwanted end-of-line.
	output << "\n[" << ss << "] " << message << endl;
}

//-------------------------[ Compute the elapse time ]------------------------//

double elapsedFrom(const time_point<system_clock> &start_time)
{
	return chrono::duration_cast<milliseconds>(
			   system_clock::now() - start_time)
			   .count() /
		   1000.0;
}

void run(RunArguments args)
{
	const auto start_time = system_clock::now();
	FileGenerator fileGenerator = FileGenerator();
	fstream output = fileGenerator.getOutputFile(args.output_file_location);

	log("Reading instance...", output);
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

	output << "population size: " << brkga_params.population_size << endl;
	output << "cromossome size: " << cromossome_size << endl;

	log("Initializing BRKGA...", output);
	algorithm.initialize();

	log("Evolving...", output);
	output << "* Iteration | Cost | CurrentTime" << endl;
	unsigned last_update_iteration = 0;
	double last_update_time;
	unsigned large_offset = 0;

	BRKGA::fitness_t best_fitness = BRKGA::FITNESS_T_MAX;
	algorithm.evolve();
	best_fitness = algorithm.getBestFitness();
	last_update_time = elapsedFrom(start_time);
	output
		<< "* " << 1 << " | "
		<< setiosflags(ios::fixed) << setprecision(0)
		<< best_fitness << " | "
		<< setiosflags(ios::fixed) << setprecision(2)
		<< last_update_time
		<< endl;
	BRKGA::Chromosome best = algorithm.getBestChromosome();
	decoder.printSolution(best, output);
	unsigned iteration = 1;
	for (iteration; iteration <= args.number_of_generations; iteration++)
	{
		algorithm.evolve();
		auto fitness = algorithm.getBestFitness();
		if (fitness < best_fitness)
		{
			last_update_time = elapsedFrom(start_time);
			best_fitness = fitness;

			auto update_offset = iteration - last_update_iteration;
			last_update_iteration = iteration;

			if (large_offset < update_offset)
				large_offset = update_offset;

			best = algorithm.getBestChromosome();

			output
				<< "* " << iteration << " | "
				<< setiosflags(ios::fixed) << setprecision(0)
				<< best_fitness << " | "
				<< setiosflags(ios::fixed) << setprecision(2)
				<< last_update_time
				<< endl;
			decoder.printSolution(best, output);
		}
	}

	const auto total_num_iterations = iteration;
	const auto total_elapsed_time = elapsedFrom(start_time);

	log("End of optimization", output);
	output
		<< "\nTotal number of iterations: " << total_num_iterations
		<< "\nLast update iteration: " << last_update_iteration
		<< "\nTotal optimization time: " << total_elapsed_time
		<< "\nLast update time: " << last_update_time
		<< "\nLarge number of iterations between improvements: " << large_offset;

	output.close();
}

int main(int argc, char const *argv[])
{
	RunArguments args(argv);
	run(args);

	return 0;
}
