#include "BRKGARunner.hpp"
#include "Constants.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

BRKGARunner::BRKGARunner(unsigned num_generations)
{
    this->num_generations = num_generations;
    TSPInstance instance = TSPInstance();
    instance.setUp();
    instance.print();
    cromossome_size = instance.size();
    if (instance.decoderType == BOTH)
        cromossome_size *= 2;
    TSPDecoder decoder(instance);
    auto [params, control_params] =
        BRKGA::readConfiguration("config.conf");
    brkga_params = params;
}

void BRKGARunner::run(int seed)
{

    BRKGA::BRKGA_MP_IPR<TSPDecoder> algorithm(
        decoder, BRKGA::Sense::MINIMIZE, seed,
        cromossome_size, brkga_params);

    const double rho = 0.7;
    algorithm.setBiasCustomFunction([&](const unsigned x)
                                    { return x == 1 ? rho : 1.0 - rho; });

    algorithm.initialize();
    algorithm.evolve(1);
    std::fstream file = std::fstream("../src/output/output.txt", std::ios::out);
    file << "Generation " << 1 << std::endl;

    BRKGA::Chromosome best = algorithm.getBestChromosome();
    decoder.printSolution(best);
    for (unsigned i = 0; i <= num_generations; i += 50)
    {
        algorithm.evolve(50);
        file << "Generation " << i + 50 << std::endl
             << std::endl;

        best = algorithm.getBestChromosome();
        decoder.printSolution(best);
    }
    file.close();
}