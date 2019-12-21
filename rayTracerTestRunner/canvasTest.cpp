//
//  canvasTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "canvas.hpp"

// ------------ Colors ------------
TEST_CASE( "Creating a canvas" ) {
    auto c = Canvas(10, 20);
    REQUIRE( c.width == 10);
    REQUIRE( c.height == 20);
    
    // Make sure all pixels initialize to black
    bool notBlack = false;
    for (auto row : c.pixels) {
        for (auto pixel : row) {
            if (!colorEquality(pixel, Color(0, 0, 0))) {
                notBlack = true;
            }
        }
    }
    REQUIRE( notBlack == false);
};

TEST_CASE( "Writing pixels to a canvas" ) {
    auto c = Canvas(10, 20);
    auto red = Color(1, 0, 0);
    writePixel(c, 2, 3, red);
    REQUIRE( colorEquality(pixelAt(c, 2, 3), red) );
}
