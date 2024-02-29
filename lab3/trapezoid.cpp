#include "trapezoid.hpp"

Trapezoid::Trapezoid(std::istream &is) {
    for (size_t i = 0; i < 4; ++i) {
        is >> points[i];
    }
}

Trapezoid::Trapezoid(Point &p1, Point &p2, Point &p3, Point &p4) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

void Trapezoid::print(std::ostream &os) const {
    for (const auto &p : points) {
        os << p << " ";
    }
    os << std::endl;
}

double Trapezoid::square() const {
    double square = 0.0;

    double a = (std::sqrt(std::pow(points[2].getX() - points[1].getX(),2) + std::pow(points[2].getY() - points[1].getY(),2)));
    double b = (std::sqrt(std::pow(points[0].getX() - points[3].getX(),2) + std::pow(points[0].getY() - points[3].getY(),2)));

    double h = std::fabs(points[1].getY() - points[0].getY());
    square = (a + b) / 2 * h;
    return floor(square * 100) / 100;
}

Point Trapezoid::center() const {
    double x = 0.0;
    double y = 0.0;

    double a = (std::sqrt(std::pow(points[2].getX() - points[1].getX(), 2) + std::pow(points[2].getY() - points[1].getY(), 2)));
    double b = (std::sqrt(std::pow(points[3].getX() - points[0].getX(), 2) + std::pow(points[3].getY() - points[0].getY(), 2)));

    double min = std::min(a,b);
    double max = std::max(a,b);

    double h = std::fabs(points[1].getY() - points[0].getY());
    
    x = floor((h / 2) * 100) / 100;
    y = floor((((2 * min + max) * h) / (3 * (min + max))) * 100) / 100;
    return Point(x,y);
}

Figure& Trapezoid::move(Figure &&other) noexcept {
    const Trapezoid *otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    for (size_t i = 0; i < 4; ++i)
        points[i] = std::move(otherTrapezoid->points[i]);
    return *this;
}

Figure& Trapezoid::operator=(const Figure &other) {
    const Trapezoid *otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    for (size_t i = 0; i < 4; ++i) {
        points[i] = otherTrapezoid->points[i];
    }
    return *this;
}

bool Trapezoid::operator==(const Figure &other) const {
    const Trapezoid *otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    for (size_t i = 0; i < 4; ++i) {
        if (points[i].getX() != otherTrapezoid->points[i].getX() || points[i].getY() != otherTrapezoid->points[i].getX()) {
            return 0;
        }
    }
    return 1;
}