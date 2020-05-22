//
//  demo.cpp
//  RayTracer
//
//  Created by Beeb on 1/1/20.
//  Copyright © 2020 Beeb. All rights reserved.
//

#include "world.hpp"
#include "camera.hpp"
#include "transformations.hpp"

void renderWorld() {
    vector<shared_ptr<Sphere>> objects;
    shared_ptr<PointLight> light(new PointLight{Point{-10, 10, -10}, Color{1, 1, 1}});
    
    shared_ptr<Sphere> floor(new Sphere);
    floor->transform = scaling(10, 0.01, 10);
    floor->material = Material{};
    floor->material.color = Color{1, 0.9, 0.9};
    floor->material.specular = 0;
    objects.push_back(floor);
    
    shared_ptr<Sphere> leftWall(new Sphere);
    leftWall->transform = translation(0, 0, 5) * rotationY(-PI/4) *
                            rotationX(PI/2) * scaling(10, 0.01, 10);
    leftWall->material = floor->material;
    objects.push_back(leftWall);
    
    shared_ptr<Sphere> rightWall(new Sphere);
    rightWall->transform = translation(0, 0, 5) * rotationY(PI/4) *
                            rotationX(PI/2) * scaling(10, 0.01, 10);
    rightWall->material = floor->material;
    objects.push_back(rightWall);
    
    shared_ptr<Sphere> middle(new Sphere);
    middle->transform = translation(-0.5, 1, 0.5);
    middle->material = Material{};
    middle->material.color = Color{0.1, 1, 0.5};
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    objects.push_back(middle);
    
    shared_ptr<Sphere> right(new Sphere);
    right->transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
    right->material = Material{};
    right->material.color = Color{0.5, 1, 0.1};
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    objects.push_back(right);
    
    shared_ptr<Sphere> left(new Sphere);
    left->transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
    left->material = Material{};
    left->material.color = Color{1, 0.8, 0.1};
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    objects.push_back(left);
    
    World world{objects, light};
    Camera camera{400, 200, PI/3};
    camera.transform = viewTransform(Point{0, 1.5, -5}, Point{0, 1, 0}, Vector{0, 1, 0});
    
    Canvas canvas = render(camera, world);
    canvasToPPM(canvas);
};
