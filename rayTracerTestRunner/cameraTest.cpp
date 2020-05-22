//
//  cameraTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 1/1/20.
//  Copyright © 2020 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "camera.hpp"
#include "world.hpp"
#include "transformations.hpp"
#include <math.h>
#include <iostream>

TEST_CASE("Constructing a camera") {
    int hsize = 160;
    int vsize = 120;
    double fov = (PI / 2);
    Camera c{hsize, vsize, fov};
    REQUIRE(c.hsize == 160);
    REQUIRE(c.vsize == 120);
    REQUIRE(c.fov == PI / 2);
    REQUIRE(c.transform == initIdentityMatrix(4));
};

TEST_CASE("The pixel size for a horizontal canvas") {
    Camera c{200, 125, PI/2};
    REQUIRE(abs(c.pixelSize - 0.01) < 0.0001);
}

TEST_CASE("The pixel size for a vertical canvas") {
    Camera c{125, 200, PI/2};
    REQUIRE(abs(c.pixelSize - 0.01) < 0.0001);
}

TEST_CASE("Constructing a ray through the center of the canvas") {
    Camera c{201, 101, PI/2};
    Ray r = rayForPixel(c, 100, 50);
    REQUIRE(r.origin == Point{0, 0, 0});
    REQUIRE(r.direction == Vector{0, 0, -1});
}

TEST_CASE("Constructing a ray through a corner of the canvas") {
    Camera c{201, 101, PI/2};
    Ray r = rayForPixel(c, 0, 0);
    REQUIRE(r.origin == Point{0, 0, 0});
    REQUIRE(r.direction == Vector{0.66519, 0.33259, -0.66851});
}

TEST_CASE("Constructing a ray when the camera is transformed") {
    Camera c{201, 101, PI/2};
    c.transform = rotationY(PI/4) * translation(0, -2, 5);
    Ray r = rayForPixel(c, 100, 50);
    REQUIRE(r.origin == Point{0, 2, -5});
    REQUIRE(r.direction == Vector{sqrt(2)/2, 0, -sqrt(2)/2});
}

TEST_CASE("Rendering a world with a camera") {
    World w = defaultWorld();
    Camera c{11 , 11, PI/2};
    Point from{0, 0, -5};
    Point to{0, 0, 0};
    Vector up{0, 1, 0};
    c.transform = viewTransform(from, to, up);
    auto image = render(c, w);
    REQUIRE(pixelAt(image, 5, 5) == Color{0.38066, 0.47583, 0.2855});
}
