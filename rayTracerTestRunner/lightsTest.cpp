//
//  lightsTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/26/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "lights.hpp"

TEST_CASE("A point light has a position and intensity") {
    Color intensity = Color{1, 1, 1};
    Point position = Point{0, 0, 0};
    PointLight light = PointLight{position, intensity};
    REQUIRE(light.position == position);
    REQUIRE(light.intensity == intensity);
}
