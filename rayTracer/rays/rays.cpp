//
//  rays.cpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "rays.hpp"

Ray::Ray(Point origin, Vector direction) : origin(origin), direction(direction) {};

Point Ray::getOrigin() { return this->origin; };
Vector Ray::getDirection() { return this->direction; };

Point position(Ray r, double t) {
    return r.getOrigin() + r.getDirection() * t;
};

Ray transform(Ray r, Matrix m) {
    return Ray(m * r.getOrigin(),
               m * r.getDirection());
};
