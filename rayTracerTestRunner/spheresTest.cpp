//
//  spheresTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "spheres.hpp"
#include "transformations.hpp"
#include "intersections.hpp"
#include <math.h>

TEST_CASE("A ray intersects a sphere at two points") {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 4.0);
    REQUIRE(xs[1].getT() == 6.0);
};

TEST_CASE("A ray intersects a sphere a tangent") {
    Ray r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 5.0);
    REQUIRE(xs[1].getT() == 5.0);
};

TEST_CASE("A ray misses a sphere") {
    Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere") {
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere s = Sphere();
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == -1.0);
    REQUIRE(xs[1].getT() == 1.0);
}

TEST_CASE("A sphere is behind a ray") {
    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere s = Sphere();
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == -6.0);
    REQUIRE(xs[1].getT() == -4.0);
}

TEST_CASE("Intersect sets the object on the intersection") {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getS() == &s);
    REQUIRE(xs[1].getS() == &s);
}

TEST_CASE("A sphere's default transformation") {
    Sphere s{};
    REQUIRE(s.transform == initIdentityMatrix(4));
}

TEST_CASE("Changing a sphere's transformation") {
    Sphere s{};
    Matrix t = translation(2, 3, 4);
    setTransform(&s, t);
    REQUIRE(s.transform == t);
}

TEST_CASE("Intersecting a scaled sphere with a ray") {
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Sphere s{};
    setTransform(&s, scaling(2, 2, 2));
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 3);
    REQUIRE(xs[1].getT() == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray") {
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Sphere s{};
    setTransform(&s, translation(5, 0, 0));
    auto xs = intersect(&s, r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("The normal on a sphere at a point on the x axis") {
    Sphere s{};
    Vector norm = normalAt(&s, Point{1, 0, 0});
    REQUIRE(norm == Vector{1, 0, 0});
}

TEST_CASE("The normal on a sphere at a point on the y axis") {
    Sphere s{};
    Vector norm = normalAt(&s, Point{0, 1, 0});
    REQUIRE(norm == Vector{0, 1, 0});
}

TEST_CASE("The normal on a sphere at a point on the z axis") {
    Sphere s{};
    Vector norm = normalAt(&s, Point{0, 0, 1});
    REQUIRE(norm == Vector{0, 0, 1});
}

TEST_CASE("The normal on a sphere at a point on a nonaxial point") {
    Sphere s{};
    Vector norm = normalAt(&s, Point{sqrt(3)/3, sqrt(3)/3, sqrt(3)/3});
    REQUIRE(norm == Vector{sqrt(3)/3, sqrt(3)/3, sqrt(3)/3});
}

TEST_CASE("The normal is a normalized vector") {
    Sphere s{};
    Vector norm = normalAt(&s, Point{sqrt(3)/3, sqrt(3)/3, sqrt(3)/3});
    REQUIRE(norm == normalize(norm));
}

TEST_CASE("Computing the normal on a translated sphere") {
    Sphere s{};
    setTransform(&s, translation(0, 1, 0));
    Vector norm = normalAt(&s, Point{0, 1.70711, -0.70711});
    REQUIRE(norm == Vector{0, 0.70711, -0.70711});
}

TEST_CASE("Computing the normal on a transformed sphere") {
    Sphere s{};
    Matrix m = scaling(1, 0.5, 1) * rotationZ(PI/5);
    setTransform(&s, m);
    Vector norm = normalAt(&s, Point{0, sqrt(2)/2, -sqrt(2)/2});
    REQUIRE(norm == Vector{0, 0.97014, -0.24254});
}

// Materials
TEST_CASE("A sphere has a default material") {
    Sphere s{};
    Material m = s.material;
    REQUIRE(m == Material{});
}

TEST_CASE("A sphere may be assigned a material") {
    Sphere s{};
    Material m{};
    m.ambient = 1;
    s.material = m;
    REQUIRE(s.material == m);
}
