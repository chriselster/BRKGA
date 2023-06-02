#include "Point.hpp"
#include <cmath>

Point::Point()
{
    _x = 0;
    _y = 0;
}

Point::Point(long double x, long double y)
{
    _x = x;
    _y = y;
}

Point::Point(const Point &other)
{
    _x = other._x;
    _y = other._y;
}

Point::~Point()
{
}

long double Point::distanceTo(Point *other)
{
    return sqrt(pow(_x - other->_x, 2) + pow(_y - other->_y, 2));
}

void Point::print()
{
    std::cout << toString() << std::endl;
}

std::string Point::toString()
{
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
}