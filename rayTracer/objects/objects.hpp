//
//  spheres.hpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef spheres_hpp
#define spheres_hpp

#include <vector>
#include "rays.hpp"
#include "materials.hpp"

class Object {
public:
    Matrix transform;
    Material material;
    
    Object(Matrix transform=initIdentityMatrix(4), Material material=Material{}) :
    transform(transform), material(material) {};
    
    void print();
    
    bool operator== (const Object& o2) const;
};

class Sphere : public Object {
public:
    Sphere() : Object() {};
    
    Sphere(Matrix transform, Material material) :
    Object(transform, material) {};
};

Vector normalAt(shared_ptr<Sphere> s, Point p);

// Demo
void drawSphere();

#endif /* spheres_hpp */
