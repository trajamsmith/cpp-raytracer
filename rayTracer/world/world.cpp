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
#include <iostream>

World defaultWorld() {
    World w{};
    
    shared_ptr<Sphere> s1(new Sphere);
    s1->material.color = Color{0.8, 1.0, 0.6};
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    w.objects.push_back(std::move(s1));
    
    shared_ptr<Sphere> s2(new Sphere);
    s2->transform = scaling(0.5, 0.5, 0.5);
    w.objects.push_back(std::move(s2));
    
    shared_ptr<PointLight> light(new PointLight{Point{-10, 10, -10}, Color{1, 1, 1}});
    w.light = light;

    return w;
};

vector<Intersection*> intersectWorld(World& w, Ray r) {
    vector<Intersection*> output{};
    
    for (int i = 0; i < w.objects.size(); i++) {
        vector<Intersection*> temp = intersect(std::move(w.objects[i]), r);
        output.insert( output.end(), temp.begin(), temp.end() );
    }
    
    std::sort(output.begin(), output.end(),
        [](Intersection* i1, Intersection* i2){
            return i1->t < i2->t;
        }
    );
    
    return output;
};

Color shadeHit(World w, Comps c) {
    return lighting(c.object->material, *w.light, c.point, c.eyeV, c.normalV);
};
