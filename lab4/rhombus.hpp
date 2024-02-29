#pragma once

#include "figure.hpp"

template <typename T>
class Rhombus : public Figure<T> {
    public:
        std::vector<std::pair<T,T> > points;

        Rhombus() {
            points.resize(4, {0, 0});
        }

        Rhombus(const std::vector<std::pair<T, T> > &v) : points(v) {
            if (v.size() != 4)
                throw std::logic_error("Rhombus must have 4 points");
        }

        typename Figure<T>::point center() const {
            T x = (points[2].first - points[0].first) / 2;
            T y = (points[1].second - points[3].second) / 2;
            return {x, y};
        }

        T square() const {
            T d1 = points[2].first - points[0].first;
            T d2 = points[1].second - points[3].second;
            T square = d1 * d2 / 2;
            return square;
        }

    Rhombus& operator=(const Rhombus<T> &other) {
        points = other.points;
        return *this;
    }   

    Rhombus& operator=(Rhombus<T> &&other) {
        points = std::move(other.points);
        return *this;
    }   

    bool operator==(const Rhombus &other) const {
        for (size_t i = 0; i < 4; ++i) {
            if (points[i] != other.points[i]) {
                return 0;
            }
        }
        return 1;
    }

    operator double() const override;

    ~Rhombus() = default;
};

template <typename T>
std::istream &operator>>(std::istream &is, Rhombus<T> &r) {
    for (size_t i = 0; i < 4; ++i) {
        is >> r.points[i].first >> r.points[i].second;
    }
    return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Rhombus<T> &r) {
    for (size_t i = 0; i < 4; ++i) {
        os << "(" << r.points[i].first << ";" << r.points[i].second << ")";
    }
    return os;
}

template <typename T>
inline Rhombus<T>::operator double() const {
    return static_cast<double>(this->square());
}