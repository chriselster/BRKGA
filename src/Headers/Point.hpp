#ifndef POINT_HPP
#define POINT_HPP
#include <cmath>
#include <iostream>
#include <string>

class Point
{
private:
    double m_x;
    double m_y;

public:
    Point();
    Point(double x, double y);
    Point(const Point &p);
    ~Point();
    double distanceTo(Point *p);
    void print();
    std::string toString();
};

#endif // POINT_HPP