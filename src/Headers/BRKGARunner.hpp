#ifndef __BRKGARUNNER_H__
#define __BRKGARUNNER_H__

#include "brkga_mp_ipr/brkga_mp_ipr.hpp"
#include "TSPInstance.hpp"
#include "TSPDecoder.hpp"
#include "Constants.hpp"

#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

class BRKGARunner
{
    BRKGA::BrkgaParams brkga_params;
    TSPInstance instance;
    TSPDecoder decoder;
    int cromossome_size;
    unsigned num_generations;
    std::string parseLine(std::fstream &file);
    std::fstream getOutputFile(int seed);

public:
    BRKGARunner(unsigned num_generations);
    void run(int seed);
};

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

    std::fstream file = getOutputFile(seed);
    file << "Generation " << 1 << std::endl;

    BRKGA::Chromosome best = algorithm.getBestChromosome();
    decoder.printSolution(best, file);
    for (unsigned i = 0; i <= num_generations; i += 50)
    {
        algorithm.evolve(50);
        file << "Generation " << i + 50 << std::endl
             << std::endl;

        best = algorithm.getBestChromosome();
        decoder.printSolution(best, file);
    }
    file.close();
}

std::fstream BRKGARunner::getOutputFile(int seed)
{
    std::fstream file;
    file.open("parameters.txt", std::ios::in);
    std::string testFolder = parseLine(file);
    testFolder += "/";
    file.close();

    std::string command = "mkdir -p " + testFolder;
    system(command.c_str());

    std::string filename = "output/testFolder" + std::to_string(seed) + ".txt";
    file.open(filename, std::ios::out);
    return file;
}

std::string BRKGARunner::parseLine(std::fstream &file)
{
    std::string line;
    std::getline(file, line);
    std::string delimiter = "= ";
    std::string parsed = line.substr(line.find(delimiter) + delimiter.length());
    return parsed;
}
#endif // __BRKGARUNNER_H__