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
    shared_ptr<Sphere> s;
    
    Intersection(double t, shared_ptr<Sphere> s) : t(t), s(move(s)) {};
    
    double getT() const { return this->t; };
    shared_ptr<Sphere> getS() { return std::move(this->s); };
    
    bool operator== (Intersection i2) {
        return (this->getT() == i2.getT() &&
                this->getS() == i2.getS());
    };
};

std::vector<Intersection*> intersect(const shared_ptr<Sphere> s, Ray r);

Intersection* hit(std::vector<Intersection*> intersects);

struct Comps {
    double t;
    shared_ptr<Sphere> object;
    Point point{0, 0, 0};
    Vector eyeV{0, 0, 0};
    Vector normalV{0, 0, 0};
    bool inside;
};

Comps prepareComputations(Intersection i, Ray r);

#endif /* intersections_hpp */
