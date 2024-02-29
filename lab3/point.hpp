#pragma once

#include <cmath>
#include <iostream>

class Point{
    public:
        Point();
        Point(double x, double y);
        Point(std::istream &is);

        double getX() const;
        double getY() const;
        double distance(Point &other);

        friend std::istream &operator>>(std::istream &is, Point &p);
        friend std::ostream &operator<<(std::ostream &os, const Point &p);
    private:
        double x_, y_;

};
