//
//  rays.hpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef rays_hpp
#define rays_hpp

#include <stdio.h>
#include "matrices.hpp"

struct Ray {
    Point origin;
    Vector direction;
    
    Ray(Point origin, Vector direction);

};

Point position(Ray r, double t);

Ray transform(Ray r, Matrix m);

#endif /* rays_hpp */
