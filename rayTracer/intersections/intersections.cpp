//
//  intersections.cpp
//  RayTracer
//
//  Created by Beeb on 12/23/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "intersections.hpp"
#include "objects.hpp"
#include <math.h>
#include <iostream>

vector<Intersection*> intersect(shared_ptr<Sphere> s, Ray origR) {
    Ray r = transform(origR, inverse(s->transform));
    
    Vector sphereToRay = r.origin - Point(0, 0, 0);
    double a = dotProduct(r.direction, r.direction);
    double b = 2 * dotProduct(r.direction, sphereToRay);
    double c = dotProduct(sphereToRay, sphereToRay) - 1;
    double discriminant = (b * b) - (4 * a * c);
    
    vector<Intersection*> i {};
    i.reserve(2);
    if (discriminant >= 0) {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        auto i1 = new Intersection{t1, s};
        auto i2 = new Intersection{t2, s};
        i.push_back(i1);
        i.push_back(i2);
    };
    
    return i;
};

Intersection* hit(std::vector<Intersection*> intersects) {
    double lowest = std::numeric_limits<double>::max();
    Intersection* nearest = nullptr;
    for (auto i : intersects) {
        if (i->getT() < lowest && i->getT() >= 0) {
            nearest = i;
            lowest = i->getT();
        }
    }
    return nearest;
};

Comps prepareComputations(Intersection i, Ray r) {
    Comps comps{};
    
    comps.t = i.getT();
    comps.object = i.getS();
    
    comps.point = position(r, comps.t);
    comps.eyeV = -(r.direction);
    comps.normalV = normalAt(comps.object, comps.point);
    comps.overPoint = comps.point + comps.normalV * EPSILON;
    
    double dot = dotProduct(comps.normalV, comps.eyeV);
    if (dot < 0) {
        comps.inside = true;
        comps.normalV = -comps.normalV;
    } else {
        comps.inside = false;
    }
    
    return comps;
};
