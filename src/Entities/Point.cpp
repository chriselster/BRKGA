#include "Point.hpp"
#include <cmath>

Point::Point()
{
    m_x = 0;
    m_y = 0;
}

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

Point::Point(const Point &p)
{
    m_x = p.m_x;
    m_y = p.m_y;
}

Point::~Point()
{
}

double Point::distanceTo(Point *p)
{
    return sqrt(pow(m_x - p->m_x, 2) + pow(m_y - p->m_y, 2));
}