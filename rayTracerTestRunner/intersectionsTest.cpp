//
//  intersectionsTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/23/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "intersections.hpp"
#include "spheres.hpp"

// Intersection
TEST_CASE("An intersection encapsulates t and object") {
    shared_ptr<Sphere> s(new Sphere{});
    Intersection i = Intersection(3.5, s);
    REQUIRE(i.getT() == 3.5);
    REQUIRE(i.getS() == s);
}

TEST_CASE("Aggregating intersections") {
    shared_ptr<Sphere> s(new Sphere{});
    Intersection i1 = Intersection(1, s);
    Intersection i2 = Intersection(2, s);
    std::vector<Intersection> xs = {i1, i2};
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 1);
    REQUIRE(xs[1].getT() == 2);
}

// Hit
TEST_CASE("The hit, when all intersections have positive t") {
    shared_ptr<Sphere> s(new Sphere{});
    Intersection i1 = Intersection(1, s);
    Intersection i2 = Intersection(2, s);
    std::vector<Intersection*> xs{&i1, &i2};
    Intersection* i = hit(xs);
    REQUIRE(i == &i1);
}

TEST_CASE("The hit, when some intersections have negative t") {
    shared_ptr<Sphere> s(new Sphere{});
    Intersection i1 = Intersection(-1, s);
    Intersection i2 = Intersection(1, s);
    std::vector<Intersection*> xs{&i1, &i2};
    Intersection* i = hit(xs);
    REQUIRE(i == &i2);
}

TEST_CASE("The hit, when all intersections have negative t") {
    shared_ptr<Sphere> s(new Sphere{});
    Intersection i1 = Intersection(-2, s);
    Intersection i2 = Intersection(-1, s);
    std::vector<Intersection*> xs{&i1, &i2};
    Intersection* i = hit(xs);
    REQUIRE(i == nullptr);
}

TEST_CASE("The hit is always the lowest nonnegative intersection") {
    shared_ptr<Sphere> s(new Sphere{});
    Intersection i1 = Intersection(5, s);
    Intersection i2 = Intersection(7, s);
    Intersection i3 = Intersection(-3, s);
    Intersection i4 = Intersection(2, s);
    std::vector<Intersection*> xs{&i1, &i2, &i3, &i4};
    Intersection* i = hit(xs);
    REQUIRE(i == &i4);
}

TEST_CASE("Precomputing the state of an intersection") {
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    shared_ptr<Sphere> shape(new Sphere{});
    Intersection i{4, shape};
    auto comps = prepareComputations(i, r);
    REQUIRE(comps.t == i.t);
    REQUIRE(comps.object == i.getS());
    REQUIRE(comps.point == Point{0, 0, -1});
    REQUIRE(comps.eyeV == Vector{0, 0, -1});
    REQUIRE(comps.normalV == Vector{0, 0, -1});
}

TEST_CASE("The hit, when an intersection occurs on the outside") {
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    shared_ptr<Sphere> shape(new Sphere{});
    Intersection i{4, shape};
    Comps comps = prepareComputations(i, r);
    REQUIRE(comps.inside == false);
}

TEST_CASE("The hit, when an intersection occurs on the inside") {
    Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
    shared_ptr<Sphere> shape(new Sphere{});
    Intersection i{1, shape};
    Comps comps = prepareComputations(i, r);
    REQUIRE(comps.point == Point{0, 0, 1});
    REQUIRE(comps.eyeV == Vector{0, 0, -1});
    REQUIRE(comps.inside == true);
    REQUIRE(comps.normalV == Vector{0, 0, -1});
}
