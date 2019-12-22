//
//  transformationsTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/21/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "transformations.hpp"
#include <math.h>
#include <iostream>

// ------------ Transformations ------------

// Translation
TEST_CASE("Multiplying by a translation matrix") {
    Matrix transform = translation(5, -3, 2);
    Point p = Point(-3, 4, 5);
    Point expected = Point(2, 1, 7);
    REQUIRE(transform * p == expected);
};

TEST_CASE("Multiplying by the inverse of a translation matrix") {
    Matrix transform = translation(5, -3, 2);
    Matrix inv = inverse(transform);
    Point p = Point(-3, 4, 5);
    Point expected = Point(-8, 7, 3);
    REQUIRE(inv * p == expected);
};

TEST_CASE("Translation does not affect vectors") {
    Matrix transform = translation(5, -3, 2);
    Vector v = Vector(-3, 4, 5);
    REQUIRE(transform * v == v);
};

// Scaling
TEST_CASE("A scaling matrix applied to a point") {
    Matrix transform = scaling(2, 3, 4);
    Point p = Point(-4, 6, 8);
    Point expected = Point(-8, 18, 32);
    REQUIRE(transform * p == expected);
};

TEST_CASE("A scaling matrix applied to a vector") {
    Matrix transform = scaling(2, 3, 4);
    Vector v = Vector(-4, 6, 8);
    Vector expected = Vector(-8, 18, 32);
    REQUIRE(transform * v == expected);
};

TEST_CASE("Multiplying by the inverse of a scaling matrix") {
    Matrix transform = scaling(2, 3, 4);
    Matrix inv = inverse(transform);
    Vector v = Vector(-4, 6, 8);
    Vector expected = Vector(-2, 2, 2);
    REQUIRE(inv * v == expected);
};

TEST_CASE("Reflection is scaling by a negative value") {
    Matrix transform = scaling(-1, 1, 1);
    Point p = Point(2, 3, 4);
    Point expected = Point(-2, 3, 4);
    REQUIRE(transform * p == expected);
};

// Rotation
TEST_CASE("Rotating a point around the x axis") {
    Point p = Point(0, 1, 0);
    Matrix halfQuarter = rotationX(PI/4);
    Matrix fullQuarter = rotationX(PI/2);
    Point exp1 = Point(0, sqrt(2)/2, sqrt(2)/2);
    Point exp2 = Point(0, 0, 1);
    REQUIRE(halfQuarter * p == exp1);
    REQUIRE(fullQuarter * p == exp2);
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction") {
    Point p = Point(0, 1, 0);
    Matrix halfQuarter = rotationX(PI/4);
    Matrix inv = inverse(halfQuarter);
    Point expected = Point(0, sqrt(2)/2, -sqrt(2)/2);
    REQUIRE(inv * p == expected);
}

TEST_CASE("Rotating a point around the y axis") {
    Point p = Point(0, 0, 1);
    Matrix halfQuarter = rotationY(PI/4);
    Matrix fullQuarter = rotationY(PI/2);
    Point exp1 = Point(sqrt(2)/2, 0, sqrt(2)/2);
    Point exp2 = Point(1, 0, 0);
    REQUIRE(halfQuarter * p == exp1);
    REQUIRE(fullQuarter * p == exp2);
}

TEST_CASE("Rotating a point around the z axis") {
    Point p = Point(0, 1, 0);
    Matrix halfQuarter = rotationZ(PI/4);
    Matrix fullQuarter = rotationZ(PI/2);
    Point exp1 = Point(-sqrt(2)/2, sqrt(2)/2, 0);
    Point exp2 = Point(-1, 0, 0);
    REQUIRE(halfQuarter * p == exp1);
    REQUIRE(fullQuarter * p == exp2);
}

// Shearing
TEST_CASE("A shearing transformation moves x in proportion to y") {
    Matrix transform = shearing(1, 0, 0, 0, 0, 0);
    Point p = Point(2, 3, 4);
    REQUIRE(transform * p == Point(5, 3, 4));
}

TEST_CASE("A shearing transformation moves x in proportion to z") {
    Matrix transform = shearing(0, 1, 0, 0, 0, 0);
    Point p = Point(2, 3, 4);
    REQUIRE(transform * p == Point(6, 3, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to x") {
    Matrix transform = shearing(0, 0, 1, 0, 0, 0);
    Point p = Point(2, 3, 4);
    REQUIRE(transform * p == Point(2, 5, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to z") {
    Matrix transform = shearing(0, 0, 0, 1, 0, 0);
    Point p = Point(2, 3, 4);
    REQUIRE(transform * p == Point(2, 7, 4));
}

TEST_CASE("A shearing transformation moves z in proportion to x") {
    Matrix transform = shearing(0, 0, 0, 0, 1, 0);
    Point p = Point(2, 3, 4);
    REQUIRE(transform * p == Point(2, 3, 6));
}

TEST_CASE("A shearing transformation moves z in proportion to y") {
    Matrix transform = shearing(0, 0, 0, 0, 0, 1);
    Point p = Point(2, 3, 4);
    REQUIRE(transform * p == Point(2, 3, 7));
}

// Composite transformations
TEST_CASE("Individual transformations are applied in sequence") {
    Point p = Point(1, 0, 1);
    Matrix A = rotationX(PI/2);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);
    Point p2 = A * p;
    REQUIRE(p2 == Point(1, -1, 0));
    Point p3 = B * p2;
    REQUIRE(p3 == Point(5, -5, 0));
    Point p4 = C * p3;
    REQUIRE(p4 == Point(15, 0, 7));
}

TEST_CASE("Chained transformations must be applied in reverse order") {
    Point p = Point(1, 0, 1);
    Matrix A = rotationX(PI/2);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);
    Matrix T = C * B * A;
    REQUIRE(T * p == Point(15, 0, 7));
}
