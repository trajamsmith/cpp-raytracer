//
//  worldTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/28/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "world.hpp"
#include "transformations.hpp"
#include <iostream>

TEST_CASE("Creating world") {
    World w{};
    REQUIRE(w.objects.size() == 0);
    REQUIRE(w.light == nullptr);
}

TEST_CASE("The default world") {
    PointLight light{Point{-10, 10, -10}, Color{1, 1, 1}};

    shared_ptr<Sphere> s1(new Sphere);
    s1->material.color = Color{0.8, 1.0, 0.6};
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    shared_ptr<Sphere> s2(new Sphere);
    s2->transform = scaling(0.5, 0.5, 0.5);

    World w = defaultWorld();
    shared_ptr<PointLight> pL(w.light);
    
    REQUIRE(*w.objects[0] == *s1);
    REQUIRE(*w.objects[1] == *s2);
    REQUIRE(*pL == light);
}

TEST_CASE("Intersect a world with a ray") {
    World w = defaultWorld();
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    vector<Intersection*> xs = intersectWorld(w, r);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0]->t == 4);
    REQUIRE(xs[1]->t == 4.5);
    REQUIRE(xs[2]->t == 5.5);
    REQUIRE(xs[3]->t == 6);
}

TEST_CASE("Shading an intersection") {
    World w = defaultWorld();
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Intersection i{4, w.objects[0]};
    Comps comps = prepareComputations(i, r);
    auto c = shadeHit(w, comps);
    REQUIRE(c == Color{0.380666, 0.47583, 0.2855});
}

TEST_CASE("Shading an intersection from the inside") {
    World w = defaultWorld();
    shared_ptr<PointLight> light(new PointLight{Point{0, 0.25, 0}, Color{1, 1, 1}});
    w.light = light;
    Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
    Intersection i{0.5, w.objects[1]};
    Comps comps = prepareComputations(i, r);
    Color c = shadeHit(w, comps);
    REQUIRE(c == Color{0.1, 0.1, 0.1});
}

TEST_CASE("The color when a ray misses") {
    World w = defaultWorld();
    Ray r{Point{0, 0, -5}, Vector{0, 1, 0}};
    Color c = colorAt(w, r);
    REQUIRE(c == Color{0, 0, 0});
}

TEST_CASE("The color when a ray hits") {
    World w = defaultWorld();
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    Color c = colorAt(w, r);
    REQUIRE(c == Color{0.38066, 0.47583, 0.2855});
}

TEST_CASE("The color with an intersection behind the ray") {
    World w = defaultWorld();
    auto outer = w.objects[0];
    outer->material.ambient = 1;
    auto inner = w.objects[1];
    inner->material.ambient = 1;
    Ray r{Point{0, 0, 0.75}, Vector{0, 0, -1}};
    Color c = colorAt(w, r);
    REQUIRE(c == outer->material.color);
}

// Shadow rays
TEST_CASE("There is no shadow when nothing is collinear with point and light") {
    World w = defaultWorld();
    Point p{0, 10, 0};
    REQUIRE(isShadowed(w, p) == false);
}

TEST_CASE("The shadow when an object is between the point and the light") {
    World w = defaultWorld();
    Point p{10, -10, 10};
    REQUIRE(isShadowed(w, p) == true);
}

TEST_CASE("There is no shadow when an object is behind the light") {
    World w = defaultWorld();
    Point p{-20, 20, -20};
    REQUIRE(isShadowed(w, p) == false);
}

TEST_CASE("There is no shadow when an object is behind the point") {
    World w = defaultWorld();
    Point p{-2, 2, -2};
    REQUIRE(isShadowed(w, p) == false);
}

TEST_CASE("shade_hit() is given an intersection in shadow") {
    World w{};
    shared_ptr<PointLight> light(new PointLight{Point{0, 0, -10}, Color{1, 1, 1}});
    w.light = light;
    shared_ptr<Sphere> s1(new Sphere);
    w.objects.push_back(s1);
    shared_ptr<Sphere> s2(new Sphere(translation(0, 0, 10), Material{}));
    w.objects.push_back(s2);
    Ray r{Point{0, 0, 5}, Vector{0, 0, 1}};
    Intersection i{4, s2};
    Comps comps = prepareComputations(i, r);
    REQUIRE(shadeHit(w, comps) == Color{0.1, 0.1, 0.1});
    
}
