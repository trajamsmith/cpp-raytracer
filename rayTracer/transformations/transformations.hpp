//
//  transformations.hpp
//  RayTracer
//
//  Created by Beeb on 12/21/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef transformations_hpp
#define transformations_hpp

#include <stdio.h>
#include "matrices.hpp"

const double PI = 3.14159265;

Matrix translation(double x, double y, double z);

Matrix scaling(double x, double y, double z);

Matrix rotationX(double r);

Matrix rotationY(double r);

Matrix rotationZ(double r);

Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy);

Matrix viewTransform(Point from, Point to, Vector up);

// Demo
void paintClock();

#endif /* transformations_hpp */
