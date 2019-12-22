//
//  demo.cpp
//  RayTracer
//
//  Created by Beeb on 12/22/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "transformations.hpp"
#include "canvas.hpp"

void paintClock() {
    Vector v = Vector(0, 200, 0);
    Point center = Point(250, 250, 0);
    Matrix rotation = rotationZ(PI/6);
    Color white = Color(1, 1, 1);
    
    Canvas c = Canvas(500, 500);
    for (int h = 0; h < 12; h++) {
        Point curr = center + v;
        writePixel(c, curr.x, curr.y, white);
        v = rotation * v;
    }
    
    canvasToPPM(c);
};
