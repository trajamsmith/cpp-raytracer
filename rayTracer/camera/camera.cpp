//
//  camera.cpp
//  RayTracer
//
//  Created by Beeb on 1/1/20.
//  Copyright © 2020 Beeb. All rights reserved.
//

#include "camera.hpp"
#include <iostream>

Camera::Camera(int hsize, int vsize, double fov) : hsize(hsize), vsize(vsize), fov(fov) {
    double halfView = tan(fov / 2);
    double aspect = (hsize / (double)vsize);
    
    if (aspect >= 1) {
        // Horizontal view
        this->halfWidth = halfView;
        this->halfHeight = halfView / aspect;
    } else {
        // Vertical view
        this->halfWidth = halfView * aspect;
        this->halfHeight = halfView;
    }
    
    this->pixelSize = (this->halfWidth * 2) / hsize;
};

void Camera::print() {
    std::cout << "HSize: " << this->hsize << std::endl;
    std::cout << "VSize: " << this->vsize << std::endl;
    std::cout << "FOV: " << this->fov << std::endl;
    std::cout << "Transform: " << std::endl;
    this->transform.print();
    std::cout << "Pixel size: " << this->pixelSize << std::endl;
    std::cout << "Half height: " << this->halfHeight << std::endl;
    std::cout << "Half width: " << this->halfWidth << std::endl;
};

Ray rayForPixel(const Camera& camera, int px, int py) {
    // The offset from the edge of the canvas to the pixel's center
    double xOffset = (px + 0.5) * camera.pixelSize;
    double yOffset = (py + 0.5) * camera.pixelSize;
    
    // The untransformed coordinates of the pixel in world space.
    // (remember that the camera looks toward -z, so +x is to the *left*)
    double worldX = camera.halfWidth - xOffset;
    double worldY = camera.halfHeight - yOffset;
    
    // Using the camera matrix, transform the canvas point and the origin,
    // and then compute the ray's direction vector.
    // (remember that the canvas is at z = -1)
    Point pixel = inverse(camera.transform) * Point{worldX, worldY, -1};
    Point origin = inverse(camera.transform) * Point{0, 0, 0};
    Vector direction = normalize(pixel - origin);
    
    return Ray{origin, direction};
};

Canvas render(const Camera& camera, const World& world) {
    Canvas image{camera.hsize, camera.vsize};
    
    for (int y = 0; y < camera.vsize; y++) {
        std::cout << "Row: " << y << std::endl;
        for (int x = 0; x < camera.hsize; x++) {
            Ray ray = rayForPixel(camera, x, y);
            Color color = colorAt(world, ray);
            writePixel(image, x, y, color);
        }
    }
    
    return image;
};
