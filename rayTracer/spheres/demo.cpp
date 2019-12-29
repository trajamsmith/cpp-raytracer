//
//  demo.cpp
//  RayTracer
//
//  Created by Beeb on 12/23/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include <stdio.h>
#include "spheres.hpp"
#include "canvas.hpp"
#include "intersections.hpp"
#include "lights.hpp"
#include <iostream>

Ray calcRay(Point orig, int col, int row) {
    Point targ{(-9.975 + col * 0.05), (-9.975 + row * 0.05), 10};
    return Ray{orig, normalize(targ - orig)};
}

Intersection* getHit(Sphere* s, Ray ray) {
    vector<Intersection*> xs = intersect(s, ray);
    auto hitInt = hit(xs);
    
    for (auto i : xs) {
        if (i != hitInt) {
            delete i;
        }
    }
    
    return hitInt;
}

void drawSphere() {
    Canvas c = Canvas(400, 400);
    // Rays originate at (0, 0 -5)
    Point orig{0, 0, -2};
    
    Sphere s{};
    s.material = Material{};
    s.material.color = Color{1, 0.2, 1};
    
    Point lightPosition{-10, 10, -10};
    Color lightColor{1, 1, 1};
    PointLight light{lightPosition, lightColor};
    
    for (int row = 0; row < 400; row++) {
        std::cout << "Row: " << row << std::endl;
        
        for (int col = 0; col < 400; col++) {
            // Calculate target on canvas
            Ray ray = calcRay(orig, col, row);
            auto hitInt = getHit(&s, ray);
            
            if (hitInt) {
                // Calculate Phong shaded color
                Point point = position(ray, hitInt->getT());
                Vector normal = normalAt(&s, point);
                Vector eye = -ray.getDirection();
                Color color = lighting(s.material, light,
                                       point, eye, normal);
                writePixel(c, col, row, color);
            }
            
            delete hitInt;
        }
    }

    canvasToPPM(c);
};
