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

class World {
public:
    vector<Sphere> objects;
    PointLight* light;
    
    World(vector<Sphere> objects={}, PointLight* light=nullptr) :
    objects(objects), light(light) {};
};

World defaultWorld();

vector<Intersection*> intersectWorld(const World& w, Ray r);

#endif /* world_hpp */
