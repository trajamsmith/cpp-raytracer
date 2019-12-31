//
//  world.cpp
//  RayTracer
//
//  Created by Beeb on 12/28/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "world.hpp"
#include "transformations.hpp"
#include "intersections.hpp"

World defaultWorld() {
    World w{};
    
    Sphere s1{};
    s1.material.color = Color{0.8, 1.0, 0.6};
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    w.objects.push_back(s1);
    
    Sphere s2{};
    s2.transform = scaling(0.5, 0.5, 0.5);
    w.objects.push_back(s2);
    
    shared_ptr<PointLight> light(new PointLight{Point{-10, 10, -10}, Color{1, 1, 1}});
    w.light = light;
    
    return w;
};

vector<Intersection*> intersectWorld(const World& w, Ray r) {
    vector<Intersection*> output{};
    
    for (auto obj : w.objects) {
        shared_ptr<Sphere> p(&obj);
        vector<Intersection*> temp = intersect(p, r);
        output.insert( output.end(), temp.begin(), temp.end() );
    }
    
    std::sort(output.begin(), output.end(),
        [](Intersection* i1, Intersection* i2){
            return i1->t < i2->t;
        }
    );
    
    return output;
};
