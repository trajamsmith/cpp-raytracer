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

class Ray {
private:
    Point origin;
    Vector direction;
public:
    Ray(Point origin, Vector direction);
    
    Point getOrigin();
    Vector getDirection();
};

Point position(Ray r, double t);

Ray transform(Ray r, Matrix m);

#endif /* rays_hpp */
