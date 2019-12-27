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
    Matrix transform = initIdentityMatrix(4);
    Material material;
    
    Sphere() = default;
};

void setTransform(Sphere *s, Matrix t);

Vector normalAt(Sphere *s, Point p);

// Demo
void drawSphere();

#endif /* spheres_hpp */
