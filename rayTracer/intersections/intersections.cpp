//
//  intersections.cpp
//  RayTracer
//
//  Created by Beeb on 12/23/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "intersections.hpp"
#include "spheres.hpp"
#include <math.h>
#include <iostream>

Intersection::Intersection(double t, Sphere* s) : t(t), s(s) {};

vector<Intersection*> intersect(Sphere* s, Ray origR) {
    Ray r = transform(origR, inverse(s->transform));
    
    Vector sphereToRay = r.getOrigin() - Point(0, 0, 0);
    double a = dotProduct(r.getDirection(), r.getDirection());
    double b = 2 * dotProduct(r.getDirection(), sphereToRay);
    double c = dotProduct(sphereToRay, sphereToRay) - 1;
    double discriminant = (b * b) - (4 * a * c);
    
    vector<Intersection*> i {};
    if (discriminant >= 0) {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        Intersection i1{t1, s};
        Intersection i2{t2, s};
        i.push_back(&i1);
        i.push_back(&i2);
    };
    
    return i;
};

Intersection* hit(std::vector<Intersection*> intersects) {
    double lowest = 1000000;
    Intersection* nearest = nullptr;
    for (auto i : intersects) {
        if (i->getT() < lowest && i->getT() >= 0) {
            nearest = i;
            lowest = i->getT();
        }
    }
    return nearest;
};
