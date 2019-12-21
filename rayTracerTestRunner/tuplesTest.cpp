//
//  main.cpp
//  RayTracer
//
//  Created by Beeb on 12/12/19.
//  Copyright © 2019 Beeb. All rights reserved.
//
#include <math.h>
#include "catch.hpp"
#include "tuples.hpp"

// ------------ Tuples ------------
TEST_CASE( "A tuple with w=1.0 is a point." ) {
    auto a = Tuple(4.3, -4.2, 3.1, 1.0);
    REQUIRE( a.x == 4.3);
    REQUIRE( a.y == -4.2);
    REQUIRE( a.z == 3.1);
    REQUIRE( a.w == 1.0);
};

TEST_CASE( "A tuple with w=0.0 is a vector." ) {
    auto a = Tuple(4.3, -4.2, 3.1, 0.0);
    REQUIRE( a.x == 4.3);
    REQUIRE( a.y == -4.2);
    REQUIRE( a.z == 3.1);
    REQUIRE( a.w == 0.0);
};

TEST_CASE( "Point() creates tuples with w=1.0" ) {
    auto p = Point(4, -4, 3);
    auto t = Tuple(4, -4, 3, 1);
    REQUIRE( p == t );
}

TEST_CASE( "Vector() creates tuples with w=0.0" ) {
    auto v = Vector(4, -4, 3);
    auto t = Tuple(4, -4, 3, 0);
    REQUIRE( v == t );
}

// ------------ Tuple Arithemtic ------------
TEST_CASE( "Two tuples with equal coords are equal" ) {
    auto t1 = Tuple(1, 2, 3, 0);
    auto t2 = Tuple(1, 2, 3, 0);
    REQUIRE( t1 == t2 );
}

TEST_CASE( "Two points with equal coords are equal" ) {
    auto p1 = Point(1, 2, 3);
    auto p2 = Point(1, 2, 3);
    REQUIRE( p1 == p2 );
}

TEST_CASE( "Two vectors with equal coords are equal" ) {
    auto v1 = Vector(1, 2, 3);
    auto v2 = Vector(1, 2, 3);
    REQUIRE( v1 == v2 );
}

TEST_CASE( "Adding two tuples" ) {
    auto t1 = Tuple(3, -2, 5, 1);
    auto t2 = Tuple(-2, 3, 1, 0);
    auto sum = t1 + t2;
    REQUIRE( sum.x == 1);
    REQUIRE( sum.y == 1);
    REQUIRE( sum.z == 6);
    REQUIRE( sum.w == 1);
}

TEST_CASE( "Subtract two points" ) {
    auto p1 = Point(3, 2, 1);
    auto p2 = Point(5, 6, 7);
    auto difference = p1 - p2;
    REQUIRE( difference.x == -2);
    REQUIRE( difference.y == -4);
    REQUIRE( difference.z == -6);
}

TEST_CASE( "Subtract a vector from a point" ) {
    auto p = Point(3, 2, 1);
    auto v = Vector(5, 6, 7);
    auto difference = subtractVectorFromPoint(p, v);
    REQUIRE( difference.x == -2);
    REQUIRE( difference.y == -4);
    REQUIRE( difference.z == -6);
}

TEST_CASE( "Subtract two vectors" ) {
    auto v1 = Vector(3, 2, 1);
    auto v2 = Vector(5, 6, 7);
    auto difference = subtractVectors(v1, v2);
    REQUIRE( difference.x == -2);
    REQUIRE( difference.y == -4);
    REQUIRE( difference.z == -6);
}

TEST_CASE( "Subtracting a vector from the zero vector" ) {
    auto zero = Vector(0, 0, 0);
    auto vector = Vector(1, -2, 3);
    auto difference = subtractVectors(zero, vector);
    REQUIRE( difference.x == -1);
    REQUIRE( difference.y == 2);
    REQUIRE( difference.z == -3);
}

TEST_CASE( "Negating a tuple" ) {
    auto tuple = Tuple(1, -2, 3, -4);
    auto expected = Tuple(-1, 2, -3, 4);
    REQUIRE( negateTuple(tuple) == expected );
}

TEST_CASE( "Multiplying a tuple by a scalar" ) {
    auto a = Tuple(1, -2, 3, -4);
    auto mult = multiplyTuple(a, 3.5);
    auto expected = Tuple(3.5, -7, 10.5, -14);
    REQUIRE( mult == expected );
}

TEST_CASE( "Multiplying a tuple by a fraction" ) {
    auto a = Tuple(1, -2, 3, -4);
    auto mult = multiplyTuple(a, 0.5);
    auto expected = Tuple(0.5, -1, 1.5, -2);
    REQUIRE( mult == expected );
}

TEST_CASE( "Dividing a tuple by a scalar" ) {
    auto a = Tuple(1, -2, 3, -4);
    auto mult = a/2;
    auto expected = Tuple(0.5, -1, 1.5, -2);
    REQUIRE( mult == expected );
}

TEST_CASE( "Computing the magnitude of a vector(1, 0, 0)" ) {
    auto v = Vector(1, 0, 0);
    REQUIRE( v.magnitude() == 1.0 );
}

TEST_CASE( "Computing the magnitude of a vector(0, 1, 0)" ) {
    auto v = Vector(0, 1, 0);
    REQUIRE( v.magnitude() == 1.0 );
}

TEST_CASE( "Computing the magnitude of a vector(0, 0, 1)" ) {
    auto v = Vector(0, 0, 1);
    REQUIRE( v.magnitude() == 1.0 );
}

TEST_CASE( "Computing the magnitude of a vector(1, 2, 3)" ) {
    auto v = Vector(1, 2, 3);
    REQUIRE( v.magnitude() == sqrt(14) );
}

TEST_CASE( "Computing the magnitude of a vector(-1, -2, -3)" ) {
    auto v = Vector(-1, -2, -3);
    REQUIRE( v.magnitude() == sqrt(14) );
}

TEST_CASE( "Normalizing a vector(4, 0, 0) gives (1, 0, 0)" ) {
    auto v = Vector(4, 0, 0);
    auto expected = Vector(1, 0, 0);
    REQUIRE( normalize(v) == expected );
}

TEST_CASE( "Normalizing a vector(1, 2, 3) gives ~(0.26726, 0.53452, 0.80178)" ) {
    auto v = Vector(1, 2, 3);
    auto mag = magnitude(v);
    auto expected = Vector(1/mag, 2/mag, 3/mag);
    REQUIRE( normalize(v) == expected );
}

TEST_CASE( "The magnitude of a normalized vector is 1" ) {
    auto v = Vector(1, 2, 3);
    auto norm = normalize(v);
    REQUIRE( magnitude(norm) == 1);
}

TEST_CASE( "The dot product of two tuples" ) {
    auto a = Vector(1, 2, 3);
    auto b = Vector(2, 3, 4);
    REQUIRE( dotProduct(a, b) == 20);
}

TEST_CASE( "The corss product of two vectors" ) {
    auto a = Vector(1, 2, 3);
    auto b = Vector(2, 3, 4);
    auto expected1 = Vector(-1, 2, -1);
    REQUIRE( crossProduct(a, b) == expected1 );
    auto expected2 = Vector(1, -2, 1);
    REQUIRE( crossProduct(b, a) == expected2 );
}
