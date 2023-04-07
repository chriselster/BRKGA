#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class CsvReader
{
private:
    std::string filename;
    std::ifstream m_file;
    char m_delimiter;

public:
    std::vector<std::vector<std::string>> rows;

    template <typename T>
    static std::vector<T> from_csv(const std::string &filename, char delimiter = ',')
    {
        std::vector<T> result;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string item;

            std::vector<std::string> tokens;
            while (std::getline(ss, item, delimiter))
            {
                tokens.push_back(item);
            }

            result.push_back(T(tokens));
        }

        return result;
    }

    CsvReader(std::string filename, char delimiter = ',')
        : m_delimiter(delimiter)
    {
        m_file.open(filename);
        if (!m_file.is_open())
        {
            throw std::runtime_error("Could not open file " + filename);
        }

        std::string line;
        std::getline(m_file, line);
        while (std::getline(m_file, line))
        {
            std::stringstream ss(line);
            std::string item;

            std::vector<std::string> tokens;
            while (std::getline(ss, item, delimiter))
            {
                tokens.push_back(item);
            }

            rows.push_back(tokens);
        }
    }

    ~CsvReader()
    {
        m_file.close();
    }

    std::vector<std::string> readLine()
    {
        std::vector<std::string> result;
        std::string line;
        if (std::getline(m_file, line))
        {
            std::string token;
            size_t pos = 0;
            while ((pos = line.find(m_delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                result.push_back(token);
                line.erase(0, pos + 1);
            }
            result.push_back(line);
        }
        return result;
    }
};
