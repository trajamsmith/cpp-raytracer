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

    Sphere s1{};
    s1.material.color = Color{0.8, 1.0, 0.6};
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    Sphere s2{};
    s2.transform = scaling(0.5, 0.5, 0.5);

    World w = defaultWorld();
    PointLight* pL = w.light;
    
    REQUIRE(w.objects[0] == s1);
    REQUIRE(w.objects[1] == s2);
    REQUIRE(*pL == light);
}

TEST_CASE("Intersect a world with a ray") {
    World w = defaultWorld();
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    auto xs = intersectWorld(w, r);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0]->t == 4);
    REQUIRE(xs[1]->t == 4.5);
    REQUIRE(xs[2]->t == 5.5);
    REQUIRE(xs[3]->t == 6);
}
