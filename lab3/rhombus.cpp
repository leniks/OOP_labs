#include "rhombus.hpp"

Rhombus::Rhombus(std::istream &is) {
    for (size_t i = 0; i < 4; ++i)
        is >> points[i];
}

Rhombus::Rhombus(Point &p1, Point &p2, Point &p3, Point &p4) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

void Rhombus::print(std::ostream &os) const {
    for (const auto &p : points) {
        os << p << " ";
    }
    os << std::endl;
}

double Rhombus::square() const {
    double square = 0.0;

    double d1 = (std::sqrt(std::pow(points[2].getX() - points[0].getX(),2) + std::pow(points[2].getY() - points[0].getY(),2)));
    double d2 = (std::sqrt(std::pow(points[1].getX() - points[3].getX(),2) + std::pow(points[1].getY() - points[3].getY(),2)));

    square = d1 * d2 / 2;
    return floor(square * 100) / 100;
}

Point Rhombus::center() const {
    double x = 0.0;
    double y = 0.0;
    x = floor((points[2].getX() + points[0].getX()) / 2 * 100) / 100;
    y = floor((points[2].getY() + points[0].getY()) / 2 * 100) / 100;
    return Point(x,y);
}

Figure& Rhombus::move(Figure &&other) noexcept {
    const Rhombus *otherRhombus = dynamic_cast<const Rhombus*>(&other);
    for (size_t i = 0; i < 4; ++i)
        points[i] = std::move(otherRhombus->points[i]);
    return *this;
}

Figure& Rhombus::operator=(const Figure &other) {
    const Rhombus *otherRhombus = dynamic_cast<const Rhombus*>(&other);
    for (size_t i = 0; i < 4; ++i)
        points[i] = otherRhombus->points[i];
    return *this;
}

bool Rhombus::operator==(const Figure &other) const {
    const Rhombus *otherRhombus = dynamic_cast<const Rhombus*>(&other);
    for (size_t i = 0; i < 4; ++i) {
        if (points[i].getX() != otherRhombus->points[i].getX() || points[i].getY() != otherRhombus->points[i].getX()) {
            return 0;
        }
    }
    return 1;
}