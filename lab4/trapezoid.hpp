#pragma once

#include "figure.hpp"

template <typename T>
class Trapezoid : public Figure<T> {
    public:
        std::vector<std::pair<T,T> > points;

        Trapezoid() {
            points.resize(4, {0, 0});
        }

        Trapezoid(const std::vector<std::pair<T, T> > &v) : points(v) {
            if (v.size() != 4)
                throw std::logic_error("Trapezoid must have 4 points");
        }

        typename Figure<T>::point center() const {
            T x = (points[2].first - points[1].first + points[3].first - points[0].first) / 2;
            T y = (points[1].second - points[0].second) / 2;
            return {x, y};
        }

        T square() const {
            T a = points[2].first - points[1].first;
            T b = points[3].first - points[0].first;

            T h = points[1].second - points[0].second;
            T square = (a + b) / 2 * h;
            return square;
        }

    Trapezoid& operator=(const Trapezoid<T> &other) {
        points = other.points;
        return *this;
    }   
    Trapezoid& operator=(Trapezoid<T> &&other) {
        points = std::move(other.points);
        return *this;
    }   

    bool operator==(const Trapezoid &other) const {
        for (size_t i = 0; i < 4; ++i) {
            if (points[i] != other.points[i]) {
                return 0;
            }
        }
    return 1;
    }

    operator double() const override;

    ~Trapezoid() = default;
};

template <typename T>
std::istream &operator>>(std::istream &is, Trapezoid<T> &r) {
    for (size_t i = 0; i < 4; ++i) {
        is >> r.points[i].first >> r.points[i].second;
    }
    return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Trapezoid<T> &r) {
    for (size_t i = 0; i < 4; ++i) {
        os << "(" << r.points[i].first << ";" << r.points[i].second << ")";
    }
    return os;
}

template <typename T>
inline Trapezoid<T>::operator double() const {
    return static_cast<double>(this->square());
}