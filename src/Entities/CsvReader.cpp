#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
class CsvReader {
public:
    static std::vector<T> from_csv(const std::string& filename, char delimiter = ',') {
        std::vector<T> result;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;

            std::vector<std::string> tokens;
            while (std::getline(ss, item, delimiter)) {
                tokens.push_back(item);
            }

            result.push_back(T(tokens));
        }

        return result;
    }
};
