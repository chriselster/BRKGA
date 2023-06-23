#ifndef __RUNARGUMENTS_H__
#define __RUNARGUMENTS_H__

#include <string>

class RunArguments
{
    std::string setOutputFileLocation()
    {
        std::string output_file_location = input_file_location;
        output_file_location.replace(output_file_location.find("input"), 5, "output");
        return output_file_location + std::to_string(seed) + ".txt";
    }

public:
    RunArguments(int seed, char const *argv[])
    {
        number_of_generations = std::stoi(argv[1]);
        input_file_location = argv[2];
        decoderType = std::stoi(argv[3]);
        setOutputFileLocation();
    }

    int number_of_generations;
    int seed;
    int decoderType;
    std::string input_file_location;
    std::string output_file_location;
};
#endif // __RUNARGUMENTS_H__