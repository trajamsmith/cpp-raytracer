//
//  intersections.hpp
//  RayTracer
//
//  Created by Beeb on 12/23/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef intersections_hpp
#define intersections_hpp

#include <stdio.h>
#include "spheres.hpp"
#include <iostream>

class Intersection {
public:
    double t;
    Sphere* s;
    
    Intersection(double t, Sphere* s);
    
    double getT() const { return this->t; };
    Sphere* getS() const { return this->s; };
    
    bool operator== (Intersection i2) const {
        return (this->getT() == i2.getT() &&
                this->getS() == i2.getS());
    };
};

std::vector<Intersection*> intersect(Sphere* s, Ray r);

Intersection* hit(std::vector<Intersection*> intersects);

#endif /* intersections_hpp */
