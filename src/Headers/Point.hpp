#ifndef POINT_HPP
#define POINT_HPP

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
};

#endif // POINT_HPP