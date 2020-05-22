//
//  transformations.cpp
//  RayTracer
//
//  Created by Beeb on 12/21/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "transformations.hpp"
#include <math.h>

Matrix translation(double x, double y, double z) {
    return Matrix({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1},
    });
};

Matrix scaling(double x, double y, double z) {
    return Matrix({
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    });
};

Matrix rotationX(double r) {
    return Matrix({
        {1, 0, 0, 0},
        {0, cos(r), -sin(r), 0},
        {0, sin(r), cos(r), 0},
        {0, 0, 0, 1},
    });
};

Matrix rotationY(double r) {
    return Matrix({
        {cos(r), 0, sin(r), 0},
        {0, 1, 0, 0},
        {-sin(r), 0, cos(r), 0},
        {0, 0, 0, 1},
    });
};

Matrix rotationZ(double r) {
    return Matrix({
        {cos(r), -sin(r), 0, 0},
        {sin(r), cos(r), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    });
};

Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    return Matrix({
        {1, xy, xz, 0},
        {yx, 1, yz, 0},
        {zx, zy, 1, 0},
        {0, 0, 0, 1},
    });
};

Matrix viewTransform(Point from, Point to, Vector up) {
    Vector forward = normalize(to - from);
    Vector upn = normalize(up);
    Vector left = crossProduct(forward, upn);
    Vector trueUp = crossProduct(left, forward);
    
    Matrix orientation = Matrix({
        {left.x, left.y, left.z, 0},
        {trueUp.x, trueUp.y, trueUp.z, 0},
        {-forward.x, -forward.y, -forward.z, 0},
        {0, 0, 0, 1}
    });
    
    return orientation * translation(-from.x, -from.y, -from.z);
};
