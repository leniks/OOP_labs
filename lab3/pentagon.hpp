#pragma once

#include "point.hpp"
#include "figure.hpp"


class Pentagon : public Figure {
    public:
        Pentagon() = default;
        Pentagon(Point &p1, Point &p2, Point &p3, Point &p4, Point &p5);
        Pentagon(std::istream &is);

        void print(std::ostream &os) const;
        double square() const;
        Point center() const;

        Figure& move(Figure &&other) noexcept;
        Figure& operator=(const Figure &other);
        bool operator==(const Figure &other) const;
        

        virtual ~Pentagon() = default;
    private:
        Point points[5];
};