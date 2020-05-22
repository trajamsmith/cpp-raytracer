//
//  camera.hpp
//  RayTracer
//
//  Created by Beeb on 1/1/20.
//  Copyright © 2020 Beeb. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "matrices.hpp"
#include "rays.hpp"
#include "canvas.hpp"
#include "world.hpp"
#include <math.h>

struct Camera {
    int hsize;
    int vsize;
    double fov;
    
    Matrix transform=initIdentityMatrix(4);
    double pixelSize;
    double halfWidth;
    double halfHeight;
    
    Camera(int hsize, int vsize, double fov);
    
    void print();
};

Ray rayForPixel(const Camera& camera, int px, int py);

Canvas render(const Camera& c, const World& w);

#endif /* camera_hpp */
