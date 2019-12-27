//
//  spheres.cpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "spheres.hpp"
#include <math.h>
#include "rays.hpp"
#include <iostream>

using namespace std;

void setTransform(Sphere *s, Matrix t) {
    s->transform = t;
};

Vector normalAt(Sphere *s, Point worldPoint) {
    Matrix init = s->transform;
    Point objectPoint = inverse(s->transform) * worldPoint;
    Vector objectNorm = objectPoint - Point{0, 0, 0};
    Vector worldNorm = transposeMatrix(inverse(s->transform)) * objectNorm;
    worldNorm.w = 0;
    return normalize(worldNorm);
};