
#include "./Headers/brkga_mp_ipr/brkga_mp_ipr.hpp"
#include "./Headers/TSPDecoder.hpp"
#include "./Headers/TSPInstance.hpp"
#include "./Headers/RunArguments.hpp"
#include "./Headers/FileGenerator.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    RunArguments args = RunArguments(argv);
    TSPInstance instance = TSPInstance(args);

    FileGenerator fileGenerator = FileGenerator();
    fstream output = fileGenerator.getOutputFile(args.output_file_location);

    instance.setUp();
    instance.loadSolution("solutions/25-UNIFORM-1.csv");
    instance.printStatistics(output);
    instance.validate();

    return 0;
}
