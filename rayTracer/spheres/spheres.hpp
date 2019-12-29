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

class Sphere {
public:
    Matrix transform;
    Material material;
    
    Sphere(Matrix transform=initIdentityMatrix(4), Material material=Material{}) :
    transform(transform), material(material) {};
    
    void print();
    
    bool operator== (const Sphere& s2) const;
};

void setTransform(Sphere *s, Matrix t);

Vector normalAt(Sphere *s, Point p);

// Demo
void drawSphere();

#endif /* spheres_hpp */
