#include <gtest/gtest.h>
#include "figures.hpp"
#include <sstream>

TEST(trapezoid, square1) {
    std::stringstream in;
    in << "1 1\n4 7\n8 7\n10 1\n";
    Trapezoid r(in);
    ASSERT_EQ(r.square(), 39.00);
}

TEST(trapezoid, square2) {
    std::stringstream in;
    in << "1 8\n4 4\n6 4\n5 8\n";
    Figure *r = new Trapezoid(in);
    ASSERT_EQ(r->square(), 12);
}

TEST(trapezoid, square3) {
    std::stringstream in;
    in << "0 0\n2 3\n5 3\n7 0\n";
    Figure *r = new Trapezoid(in);
    ASSERT_EQ(r->square(), 15);
}

TEST(trapezoid, square4) {
    std::stringstream in;
    in << "-2 10\n0 13\n3 13\n5 10\n";
    Figure *r = new Trapezoid(in);
    ASSERT_EQ(r->square(), 15);
}

TEST(trapezoid, center1) {
    std::stringstream in;
    in << "1 1\n4 7\n8 7\n10 1\n";
    Trapezoid r(in);
    ASSERT_EQ(r.center().getX(), 3.00);
    ASSERT_EQ(r.center().getY(), 2.61);
}

TEST(rhombus, square1) {
    std::stringstream in;
    in << "1 6\n4 10\n7 6\n4 2\n";
    Rhombus r(in);
    ASSERT_EQ(r.square(), 24.00);
}

TEST(rhombus, square2) {
    std::stringstream in;
    in << "2 5\n6 6\n5 2\n1 1\n";
    Figure *r = new Rhombus(in);
    ASSERT_EQ(r->square(), 15.00);
}

TEST(rhombus, square3) {
    std::stringstream in;
    in << "4 4\n8 0\n4 -4\n0 0\n";
    Figure *r = new Rhombus(in);
    ASSERT_EQ(r->square(), 32.00);
}

TEST(rhombus, square4) {
    std::stringstream in;
    in << "4 3\n7 0\n4 -3\n1 0\n";
    Figure *r = new Rhombus(in);
    ASSERT_EQ(r->square(), 18.00);
}

TEST(rhombus, center1) {
    std::stringstream in;
    in << "7 6\n10 7\n9 4\n6 3\n";
    Rhombus r(in);
    ASSERT_EQ(r.center().getX(), 8.00);
    ASSERT_EQ(r.center().getY(), 5.00);
}

TEST(rhombus, center2) {
    std::stringstream in;
    in << "4 3\n7 0\n4 -3\n1 0\n";
    Rhombus r(in);
    ASSERT_EQ(r.center().getX(), 4.00);
    ASSERT_EQ(r.center().getY(), 0.00);
}

TEST(rhombus, center3) {
    std::stringstream in;
    in << "-1.5 100\n-24.1 95\n-1.5 90\n21.1 95\n";
    Rhombus r(in);
    ASSERT_EQ(r.center().getX(), -1.5);
    ASSERT_EQ(r.center().getY(), 95);
}

TEST(pentagon, square1) {
    std::stringstream in;
    in << "0 0\n2 0\n2 3\n1 4\n0 3\n";
    Pentagon r(in);
    ASSERT_EQ(r.square(), 7.00);
}

TEST(pentagon, square2) {
    std::stringstream in;
    in << "1 2\n3 1\n4 3\n3 5\n1 4\n";
    Figure *r = new Pentagon(in);
    ASSERT_EQ(r->square(), 8.00);
}

TEST(pentagon, square3) {
    std::stringstream in;
    in << "-2 0\n-1 2\n1 2\n2 0\n0 -2\n";
    Figure *r = new Pentagon(in);
    ASSERT_EQ(r->square(), 10.00);
}


TEST(pentagon, center) {
    std::stringstream in;
    in << "-2 0\n-1 2\n1 2\n2 0\n0 -2\n";
    Pentagon r(in);
    ASSERT_EQ(r.center().getX(), 0.00);
    ASSERT_EQ(r.center().getY(), 0.40);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}