#include "./catch/catch_amalgamated.hpp"
#include "../Headers/PathOptimizer.hpp"
#include "../Headers/Point.hpp"

TEST_CASE("Get shortest path"){
    PathOptimizer pathOptimizer = PathOptimizer();
    pathOptimizer.addPoint(new Point(0, 0));
    pathOptimizer.addPoint(new Point(0, 1));
    pathOptimizer.addPoint(new Point(1, 1));
    pathOptimizer.addPoint(new Point(1, 0));
    REQUIRE(pathOptimizer.getShortestPath() == 4);
}