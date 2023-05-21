#ifndef POINT_HPP
#define POINT_HPP
#include <cmath>
#include <iostream>
#include <string>

class Point
{
private:
    long double m_x;
    long double m_y;

public:
    Point();
    Point(long double x, long double y);
    Point(const Point &p);
    ~Point();
    long double distanceTo(Point *p);
    void print();
    std::string toString();
};

#endif // POINT_HPP