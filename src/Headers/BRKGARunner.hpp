#include <utility>

#include "./Headers/TSPInstance.hpp"
#include "./Headers/TSPDecoder.hpp"
#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"

class BRKGARunner
{
    BRKGA::BrkgaParams brkga_params;
    TSPInstance instance;
    TSPDecoder decoder;
    int cromossome_size;
    unsigned num_generations;

public:
    BRKGARunner(unsigned num_generations);
    void run(int seed);
};