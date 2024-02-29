#pragma once

#include "figure.hpp"

template <typename T>
class Pentagon : public Figure<T> {
    public:
        std::vector<std::pair<T,T>> points;

        Pentagon() {
            points.resize(5, {0, 0});
        }

        Pentagon(const std::vector<std::pair<T, T>> &v) : points(v) {
            if (v.size() != 5)
                throw std::logic_error("Pentagon must have 5 points");
        }

        typename Figure<T>::point center() const {
            T x = 0.0;
            T y = 0.0;
            for (size_t i = 0; i < 5; ++i) {
                x += points[i].first;
                y += points[i].second;
            }
            x /= 5.0;
            y /= 5.0;
            return {x, y};
        }

        T square() const {
            T square = 0.5 * std::abs(points[0].first * points[1].second - points[1].first * points[0].second +
                            points[1].first * points[2].second - points[2].first * points[1].second +
                            points[2].first * points[3].second - points[3].first * points[2].second +
                            points[3].first * points[4].second - points[4].first * points[3].second +
                            points[4].first * points[0].second - points[0].first * points[4].second);

            return square;
        }

    Pentagon& operator=(const Pentagon<T> &other) {
        points = other.points;
        return *this;
    }   
    Pentagon& operator=(Pentagon<T> &&other) {
        points = std::move(other.points);
        return *this;
    }   

    bool operator==(const Pentagon &other) const {
        for (size_t i = 0; i < 5; ++i) {
            if (points[i] != other.points[i]) {
                return 0;
            }
        }
    return 1;
    }

    operator double() const override;

    ~Pentagon() = default;
};

template <typename T>
std::istream &operator>>(std::istream &is, Pentagon<T> &pent) {
    for (size_t i = 0; i < 5; ++i) {
        is >> pent.points[i].first >> pent.points[i].second;
    }
    return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Pentagon<T> &pent) {
    for (size_t i = 0; i < 5; ++i) {
        os << "(" << pent.points[i].first << ";" << pent.points[i].second << ")";
    }
    return os;
}

template <typename T>
inline Pentagon<T>::operator double() const {
    return static_cast<double>(this->square());
}