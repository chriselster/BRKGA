#include "PathOptimizer.hpp"

PathOptimizer::PathOptimizer(std::vector<Point *>)
{
    for (int i = 0; i < points.size(); i++)
    {
        addPoint(points[i]);
    }
}

double PathOptimizer::getShortestPath()
{
    std::vector<int> path;
    for (int i = 0; i < points.size(); i++)
    {
        path.push_back(i);
    }
    double shortestPath = 0;
    do
    {
        double pathDistance = 0;
        for (int i = 0; i < path.size() - 1; i++)
        {
            pathDistance += distanceMatrix[path[i]][path[i + 1]];
        }
        if (shortestPath == 0 || pathDistance < shortestPath)
        {
            shortestPath = pathDistance;
        }
    } while (std::next_permutation(path.begin(), path.end()));
    return shortestPath;
}
void PathOptimizer::addPoint(Point *point)
{
    points.push_back(point);
    distanceMatrix.resize(points.size());
    for (int i = 0; i < points.size(); i++)
    {
        distanceMatrix[i].resize(points.size());
    }
    int lastPointIndex = points.size() - 1;
    for (int i = 0; i < points.size(); i++)
    {
        double distance = points[i]->distanceTo(point);
        distanceMatrix[i][lastPointIndex] = distance;
        distanceMatrix[lastPointIndex][i] = distance;
    }
}
