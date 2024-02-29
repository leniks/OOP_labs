#pragma once

#include <iostream>
#include <vector>
#include <utility>

template <typename T>
class Figure {
    public:
        using point = std::pair<T, T>;
        Figure() = default;

        virtual point center() const = 0;
        virtual T square() const = 0;

        virtual ~Figure() = default;
        virtual operator double() const {
            return 0.00;
        }
};