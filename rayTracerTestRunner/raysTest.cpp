//
//  raysTest.cpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "rays.hpp"
#include "transformations.hpp"

TEST_CASE("Creatinga and querying a ray") {
    Point origin = Point(1, 2, 3);
    Vector direction = Vector(4, 5, 6);
    Ray r = Ray(origin, direction);
    REQUIRE(r.getOrigin() == origin);
    REQUIRE(r.getDirection() == direction);
};

TEST_CASE("Computing a point from a distance") {
    Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));
    REQUIRE(position(r, 0) == Point(2, 3, 4));
    REQUIRE(position(r, 1) == Point(3, 3, 4));
    REQUIRE(position(r, -1) == Point(1, 3, 4));
    REQUIRE(position(r, 2.5) == Point(4.5, 3, 4));
}

TEST_CASE("Translating a ray") {
    Ray r{Point(1, 2, 3), Vector(0, 1, 0)};
    Matrix m = translation(3, 4, 5);
    Ray r2 = transform(r, m);
    REQUIRE(r2.getOrigin() == Point(4, 6, 8));
    REQUIRE(r2.getDirection() == Vector(0, 1, 0));
}

TEST_CASE("Scaling a ray") {
    Ray r{Point(1, 2, 3), Vector(0, 1, 0)};
    Matrix m = scaling(2, 3, 4);
    Ray r2 = transform(r, m);
    REQUIRE(r2.getOrigin() == Point(2, 6, 12));
    REQUIRE(r2.getDirection() == Vector(0, 3, 0));
}
