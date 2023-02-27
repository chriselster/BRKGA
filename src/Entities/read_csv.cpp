#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
vector<vector<T>> read_csv(const string& filename, bool header=true) {
    vector<vector<T>> data;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    string line;
    while (getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }
        stringstream ss(line);
        vector<T> row;
        string cell;
        while (getline(ss, cell, ',')) {
            stringstream converter(cell);
            T value;
            converter >> value;
            row.push_back(value);
        }
        data.push_back(row);
    }
    file.close();
    return data;
}
