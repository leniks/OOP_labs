#include "point.hpp"

Point::Point() : x_(0.0), y_(0.0){};

Point::Point(double x, double y) : x_(x), y_(y){};

Point::Point(std::istream &is) {
    is >> x_ >> y_;
}

double Point::getX() const {
    return x_;
}

double Point::getY() const {
    return y_;
}

double Point::distance(Point &other) {
    return std::sqrt((other.x_ - x_) * (other.x_ - x_) + (other.y_ - y_) * (other.y_ - y_));
}

std::istream &operator>>(std::istream &is, Point &p) {
    is >> p.x_ >> p.y_;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "(" << p.x_ << ";" << p.y_ << ")";
    return os;
}