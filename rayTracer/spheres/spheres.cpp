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

bool Sphere::operator== (const Sphere& s2) const {
    return (this->transform == s2.transform &&
            this->material == s2.material);
};

void Sphere::print() {
    cout << "Transform ------------" << endl;
    this->transform.print();
    cout << "Material ------------" << endl;
    this->material.print();
}
 
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
