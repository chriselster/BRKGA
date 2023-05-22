
#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"
#include "./Headers/TSPDecoder.hpp"
#include "./Headers/TSPInstance.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    TSPInstance instance = TSPInstance();

    instance.setUp();
    instance.loadSolution("solution.csv");

    instance.validate();
    instance.printStatistics();

    return 0;
}
