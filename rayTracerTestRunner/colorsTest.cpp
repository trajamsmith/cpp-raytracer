//
//  colorsTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "colors.hpp"

double e = .0001;

// ------------ Colors ------------
TEST_CASE( "Colors are (red, green, blue) tuples" ) {
    auto c = Color(-0.5, 0.4, 1.7);
    REQUIRE( c.red == -0.5);
    REQUIRE( c.green == 0.4);
    REQUIRE( c.blue == 1.7);
};

// ------------ Color Arithmetic ------------
TEST_CASE( "Adding colors" ) {
    auto c1 = Color(0.9, 0.6, 0.75);
    auto c2 = Color(0.7, 0.1, 0.25);
    auto expected = Color(1.6, 0.7, 1.0);
    REQUIRE(c1 + c2 == expected);
};

TEST_CASE( "Subtracting colors" ) {
    auto c1 = Color(0.9, 0.6, 0.75);
    auto c2 = Color(0.7, 0.1, 0.25);
    auto s = c1 - c2;
    REQUIRE( s.red - 0.2 < e);
    REQUIRE( s.green == 0.5);
    REQUIRE( s.blue == 0.5);
};

TEST_CASE( "Multiplying a color by a scalar" ) {
    auto c = Color(0.2, 0.3, 0.4);
    auto expected = Color(0.4, 0.6, 0.8);
    REQUIRE(c * 2 == expected);
};

TEST_CASE( "Multiply two colors" ) {
    auto c1 = Color(1, 0.2, 0.4);
    auto c2 = Color(0.9, 1, 0.1);
    auto m = c1 * c2;
    REQUIRE( m.red - 0.9 < e);
    REQUIRE( m.green - 0.2 < e);
    REQUIRE( m.blue - 0.04 < e);
};
