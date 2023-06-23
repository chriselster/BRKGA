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

class FileGenerator
{
    std::string parseLine(std::fstream &file);

public:
    std::fstream getOutputFile(int seed);
};

std::fstream FileGenerator::getOutputFile(int seed)
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

std::string FileGenerator::parseLine(std::fstream &file)
{
    std::string line;
    std::getline(file, line);
    std::string delimiter = "= ";
    std::string parsed = line.substr(line.find(delimiter) + delimiter.length());
    return parsed;
}
#endif // __BRKGARUNNER_H__