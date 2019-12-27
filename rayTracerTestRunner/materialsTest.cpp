//
//  materialsTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/26/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "materials.hpp"
#include "tuples.hpp"
#include "lights.hpp"

TEST_CASE("The default material") {
    Material m{};
    REQUIRE(m.color == Color{1, 1, 1});
    REQUIRE(m.ambient == 0.1);
    REQUIRE(m.diffuse == 0.9);
    REQUIRE(m.specular == 0.9);
    REQUIRE(m.shininess == 200.0);
}

TEST_CASE("Lighting with the eye between the light and the surface") {
    Material m{};
    Point position{0, 0, 0};
    
    Vector eyev{0, 0, -1};
    Vector normalv{0, 0, -1};
    PointLight light{Point{0, 0, -10}, Color{1, 1, 1}};
    Color result = lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color{1.9, 1.9, 1.9});
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45 degrees") {
    Material m{};
    Point position{0, 0, 0};
    
    Vector eyev{0, sqrt(2)/2, -sqrt(2)/2};
    Vector normalv{0, 0, -1};
    PointLight light{Point{0, 0, -10}, Color{1, 1, 1}};
    Color result = lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color{1.0, 1.0, 1.0});
}

TEST_CASE("Lighting with the eye opposite surface, light offset 45 degrees") {
    Material m{};
    Point position{0, 0, 0};
    
    Vector eyev{0, 0, -1};
    Vector normalv{0, 0, -1};
    PointLight light{Point{0, 10, -10}, Color{1, 1, 1}};
    Color result = lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color{0.7364, 0.7364, 0.7364});
}

TEST_CASE("Lighting with eye in the path of the reflection vector") {
    Material m{};
    Point position{0, 0, 0};
    
    Vector eyev{0, -sqrt(2)/2, -sqrt(2)/2};;
    Vector normalv{0, 0, -1};
    PointLight light{Point{0, 10, -10}, Color{1, 1, 1}};
    Color result = lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color{1.6364, 1.6364, 1.6364});
}

TEST_CASE("Lighting with the light behind the surface") {
    Material m{};
    Point position{0, 0, 0};
    
    Vector eyev{0, 0, -1};;
    Vector normalv{0, 0, -1};
    PointLight light{Point{0, 0, 10}, Color{1, 1, 1}};
    Color result = lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color{0.1, 0.1, 0.1});
}
