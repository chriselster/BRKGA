#include "./catch/catch_amalgamated.hpp"
#include "../Headers/PathOptimizer.hpp"
#include "../Headers/Point.hpp"

TEST_CASE("Get shortest path")
{
    PathOptimizer pathOptimizer = PathOptimizer(std::vector<Point *>());
    pathOptimizer.addPoint(new Point(0, 1));
    pathOptimizer.addPoint(new Point(1, 1));
    pathOptimizer.addPoint(new Point(1, 0));
    REQUIRE(pathOptimizer.getShortestPath() == 3);
    pathOptimizer.addPoint(new Point(0, 2));
    REQUIRE(pathOptimizer.getShortestPath() == 4);
}