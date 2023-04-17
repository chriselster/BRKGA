#include <vector>
#include <algorithm>
#include "Point.hpp"

class PathOptimizer
{
private:
    std::vector<Point *> points = std::vector<Point *>();
    std::vector<std::vector<double>> distanceMatrix = std::vector<std::vector<double>>();

public:
    PathOptimizer(std::vector<Point *>);
    double getShortestPath();
    void addPoint(Point *);
};