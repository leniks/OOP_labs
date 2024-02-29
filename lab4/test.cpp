#include <gtest/gtest.h>

#include "../include/figures.hpp"
#include <sstream>

TEST(pentagon, square) {
    std::stringstream stream;
    stream << "0 0\n2 0\n2 3\n1 4\n0 3\n";
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (stream >> x >> y) {
        points.emplace_back(x, y);
    }
    Pentagon<double> p(points);
    ASSERT_EQ(p.square(), 7.00);
}

TEST(pentagon, center) {
    std::stringstream stream;
    stream << "-2 0\n-1 2\n1 2\n2 0\n0 -2\n";
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (stream >> x >> y) {
        points.emplace_back(x, y);
    }
    Pentagon<double> r(points);
    ASSERT_EQ(r.center().first, 0.0);
    ASSERT_EQ(r.center().second, 0.4);
}

TEST(rhombus, square) {
    std::stringstream stream;
    stream << "1 6\n4 10\n7 6\n4 2\n";
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (stream >> x >> y) {
        points.emplace_back(x, y);
    }
    Rhombus<double> r(points);
    ASSERT_EQ(r.square(), 24.0);
}

TEST(rhombus, center) {
    std::stringstream stream;
    stream << "1 6\n4 10\n7 6\n4 2\n";
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (stream >> x >> y) {
        points.emplace_back(x, y);
    }
    Rhombus<double> r(points);
    ASSERT_EQ(r.center().first, 3.0);
    ASSERT_EQ(r.center().second, 4.0);
}

TEST(trapezoid, square) {
    std::stringstream stream;
    stream << "1 1\n2 4\n4 4\n5 1\n";
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (stream >> x >> y) {
        points.emplace_back(x, y);
    }
    Trapezoid<double> t(points);
    ASSERT_EQ(t.square(), 9.0);
}

TEST(trapezoid, center) {
    std::stringstream stream;
    stream << "1 1\n2 4\n4 4\n5 1\n";
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (stream >> x >> y) {
        points.emplace_back(x, y);
    }
    Trapezoid<double> t(points);
    ASSERT_EQ(t.center().first, 3.00);
    ASSERT_EQ(t.center().second, 1.5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   