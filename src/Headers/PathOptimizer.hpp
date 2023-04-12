
class PathOptimizer{
    private:
    std::vector<Point *> points;
    std::vector<std::vector<double>> distanceMatrix;
    public:
    PathOptimizer(std::vector<Point *>);
    double getShortestPath();
    void addPoint(Point *);
}