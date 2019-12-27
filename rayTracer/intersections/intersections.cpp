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

vector<Intersection> intersect(Sphere* s, Ray origR) {
    Ray r = transform(origR, inverse(s->transform));
    
    Vector sphereToRay = r.getOrigin() - Point(0, 0, 0);
    double a = dotProduct(r.getDirection(), r.getDirection());
    double b = 2 * dotProduct(r.getDirection(), sphereToRay);
    double c = dotProduct(sphereToRay, sphereToRay) - 1;
    double discriminant = (b * b) - (4 * a * c);
    
    vector<Intersection> i {};
    if (discriminant >= 0) {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        i.push_back(Intersection{t1, s});
        i.push_back(Intersection{t2, s});
    };
    
    return i;
};

Intersection hit(const vector<Intersection> intersects) {
    double lowest = 1000000;
    Intersection nearest{0, nullptr};
    for (auto i : intersects) {
        std::cout << "Hitting here" << std::endl;
        if (i.getT() < lowest && i.getT() >= 0) {
            nearest = i;
            lowest = i.getT();
        }
    }
    return nearest;
};
