#ifndef __RUNARGUMENTS_H__
#define __RUNARGUMENTS_H__

#include <string>

class RunArguments
{
    void setOutputFileLocation()
    {
        output_file_location = input_file_location;
        try
        {
            output_file_location.replace(output_file_location.find("instances"), 9, "outputs");
        }
        catch (const std::exception &e)
        {
            output_file_location.replace(output_file_location.find("solutions"), 9, "outputs");
        }
        std::string decoder = getDecoderName();
        output_file_location = output_file_location + decoder + "/" + std::to_string(seed) + +".txt";
    }

    std::string getDecoderName()
    {
        switch (decoderType)
        {
        case 0:
            return "only_items";
        case 1:
            return "only_vehicles";
        case 2:
            return "both";
        default:
            return "Invalid";
        }
    }

public:
    RunArguments(char const *argv[])
    {
        number_of_generations = std::stoi(argv[1]);
        input_file_location = argv[2] + std::string("/");
        decoderType = std::stoi(argv[3]);
        seed = std::stoi(argv[4]);
        setOutputFileLocation();
    }

    int number_of_generations;
    int seed;
    int decoderType;
    std::string input_file_location;
    std::string output_file_location;
};
#endif // __RUNARGUMENTS_H__