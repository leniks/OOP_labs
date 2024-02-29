#pragma once

#include <iostream>
#include <vector>

#include "point.hpp"

class Figure {
    public:
        virtual Figure& move(Figure &&other) noexcept = 0;
        virtual Figure& operator=(const Figure &other) = 0;
        virtual bool operator==(const Figure &other) const = 0;

        virtual void print(std::ostream &os) const = 0;
        virtual double square() const = 0;
        virtual Point center() const = 0;

        virtual ~Figure() = default;
};