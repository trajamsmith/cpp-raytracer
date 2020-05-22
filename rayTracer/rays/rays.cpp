//
//  rays.cpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "rays.hpp"

Ray::Ray(Point origin, Vector direction) : origin(origin), direction(direction) {};

Point position(Ray r, double t) {
    return r.origin + r.direction * t;
};

Ray transform(Ray r, Matrix m) {
    return Ray(m * r.origin,
               m * r.direction);
};
