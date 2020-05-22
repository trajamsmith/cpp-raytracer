//
//  spheres.cpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "objects.hpp"
#include <math.h>
#include "rays.hpp"
#include <iostream>

using namespace std;

void Object::print() {
    cout << "Transform ------------" << endl;
    this->transform.print();
    cout << "Material ------------" << endl;
    this->material.print();
}

bool Object::operator== (const Object& o2) const {
    return (this->transform == o2.transform &&
            this->material == o2.material);
};
 
void setTransform(shared_ptr<Sphere> s, Matrix t) {
    s->transform = t;
};

Vector normalAt(shared_ptr<Sphere> s, Point worldPoint) {
    Point objectPoint = inverse(s->transform) * worldPoint;
    Vector objectNorm = objectPoint - Point{0, 0, 0};
    Vector worldNorm = transposeMatrix(inverse(s->transform)) * objectNorm;
    worldNorm.w = 0;
    return normalize(worldNorm);
};
