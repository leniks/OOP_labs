#include "pentagon.hpp"

Pentagon::Pentagon(std::istream &is) {
    for (size_t i = 0; i < 5; ++i)
        is >> points[i];
}

Pentagon::Pentagon(Point &p1, Point &p2, Point &p3, Point &p4, Point &p5) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
}

void Pentagon::print(std::ostream &os) const {
    for (const auto &p : points) {
        os << p << " ";
    }
    os << std::endl;
}

double Pentagon::square() const {
    double square = 0.0;
    square = 0.5 * std::abs(points[0].getX() * points[1].getY() - points[1].getX() * points[0].getY() +
                            points[1].getX() * points[2].getY() - points[2].getX() * points[1].getY() +
                            points[2].getX() * points[3].getY() - points[3].getX() * points[2].getY() +
                            points[3].getX() * points[4].getY() - points[4].getX() * points[3].getY() +
                            points[4].getX() * points[0].getY() - points[0].getX() * points[4].getY());

    return floor(square * 100) / 100;
}

Point Pentagon::center() const {
    double x = 0.0;
    double y = 0.0;

    for (size_t i = 0; i < 5; ++i){
        x += points[i].getX();
        y += points[i].getY();
    }

    x /= 5.0;
    y /= 5.0;

    return Point(x, y);
}

Figure &Pentagon::move(Figure &&other) noexcept {
    const Pentagon *otherPentagon = dynamic_cast<const Pentagon *>(&other);
    for (size_t i = 0; i < 5; ++i)
        points[i] = std::move(otherPentagon->points[i]);
    return *this;
}

Figure &Pentagon::operator=(const Figure &other) {
    const Pentagon *otherPentagon = dynamic_cast<const Pentagon *>(&other);
    for (size_t i = 0; i < 5; ++i)
        points[i] = otherPentagon->points[i];
    return *this;
}

bool Pentagon::operator==(const Figure &other) const {
    const Pentagon *otherPentagon = dynamic_cast<const Pentagon *>(&other);
    for (size_t i = 0; i < 5; ++i) {
        if (points[i].getX() != otherPentagon->points[i].getX() || points[i].getY() != otherPentagon->points[i].getX()) {
            return 0;
        }
    }
    return 1;
}