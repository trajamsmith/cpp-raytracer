//
//  world.hpp
//  RayTracer
//
//  Created by Beeb on 12/28/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <vector>
#include "lights.hpp"
#include "spheres.hpp"
#include "intersections.hpp"

struct World {
    vector<shared_ptr<Sphere>> objects;
    shared_ptr<PointLight> light;
    
    World(vector<shared_ptr<Sphere>> objects={}, shared_ptr<PointLight> light=nullptr) :
    objects(std::move(objects)), light(light) {};
};

World defaultWorld();

vector<Intersection*> intersectWorld(const World& w, Ray r);

Color shadeHit(World w, Comps c);

#endif /* world_hpp */
