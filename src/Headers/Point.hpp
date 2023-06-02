#ifndef POINT_HPP
#define POINT_HPP
#include <cmath>
#include <iostream>
#include <string>

class Point
{
private:
    long double _x;
    long double _y;

public:
    Point();
    Point(long double x, long double y);
    Point(const Point &other);
    ~Point();
    long double distanceTo(Point *other);
    void print();
    std::string toString();
};

#endif // POINT_HPP