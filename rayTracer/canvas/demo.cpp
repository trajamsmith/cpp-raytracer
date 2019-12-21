//
//  demo.cpp
//  RayTracer
//
//  Created by Beeb on 12/20/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "canvas.hpp"
#include "tuples.hpp"

void paintCannonTrajectory() {
    Point start = Point(0, 1, 0);
    Vector velocity = multiplyTuple(normalize(Vector(1, 1.8, 0)), 11.25);
    Projectile p = Projectile(start, velocity);
    
    Vector gravity = Vector(0, -0.1, 0);
    Vector wind = Vector(-0.01, 0, 0);
    Environment e = Environment(gravity, wind);
    
    Canvas c = Canvas(900, 550);
    
    int i = 0;
    int x, y;
    Color red = Color(1, 0, 0);
    while (p.position.y > 0) {
        p = tick(e, p);
        x = int(round(p.position.x));
        y = 550 - int(round(p.position.y));
        std::cout << x << " " << y << std::endl;
        writePixel(c, x, y, red);
        i++;
    }
    
    canvasToPPM(c);
};
