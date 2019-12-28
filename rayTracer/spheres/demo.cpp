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

void drawSphere() {
    Canvas c = Canvas(400, 400);
    // Rays originate at (0, 0 -5)
    Point orig{0, 0, -5};
    
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
            Point targ{(-9.975 + col * 0.05), (-9.975 + row * 0.05), 10};
            Ray ray{orig, normalize(targ - orig)};
            
            auto xs = intersect(&s, ray);
            Intersection* hitInt = hit(xs);
            
            if (hitInt) {
                // Calculate Phong shaded color
                Point point = position(ray, hitInt->getT());
                Vector normal = normalAt(hitInt->getS(), point);
                Vector eye = -ray.getDirection();
                Color color = lighting(hitInt->getS()->material, light,
                                       point, eye, normal);
                
                writePixel(c, col, row, color);
            }
        }
    }

    canvasToPPM(c);
};
