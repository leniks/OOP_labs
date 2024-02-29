#pragma once

#include "point.hpp"
#include "figure.hpp"


class Rhombus : public Figure {
    public:
        Rhombus() = default;
        Rhombus(Point &p1, Point &p2, Point &p3, Point &p4);
        Rhombus(std::istream &is);

        void print(std::ostream &os) const;
        double square() const;
        Point center() const;

        Figure& move(Figure &&other) noexcept;
        Figure& operator=(const Figure &other);
        bool operator==(const Figure &other) const;
        

        virtual ~Rhombus() = default;
    private:
        Point points[4];
};