#include "Client.hpp"

#include <fstream>
#include <sstream>
#include <string>

Client::Client()
{
    std::ifstream file;
    file.open("clients.csv");
    std::string line;
    std::vector<std::string> tokens;
    while (std::getline(file, line))
    {
        std::stringstream stringStream(line);
        std::string token;
        while (std::getline(stringStream, token, ','))
        {
            tokens.push_back(token);
        }
    }
    file.close();

    this->id = std::stoi(tokens[0]);
    this->x = std::stod(tokens[1]);
    this->y = std::stod(tokens[2]);
}