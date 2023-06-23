#ifndef __FILEGENERATOR_H__
#define __FILEGENERATOR_H__

#include <string>
#include <fstream>
#include <filesystem>
#include <stdlib.h>

class FileGenerator
{
    std::string getFolder(std::string file_location);

public:
    std::fstream getOutputFile(std::string file_location);
};

std::fstream FileGenerator::getOutputFile(std::string file_location)
{
    std::string folder = getFolder(file_location);
    std::filesystem::create_directory(file_location);

    std::fstream file;
    file.open(file_location, std::ios::out);
    return file;
}

std::string FileGenerator::getFolder(std::string file_location)
{
    std::string folder = file_location.substr(0, file_location.find_last_of("/\\"));
    return folder;
}

#endif // __FILEGENERATOR_H__