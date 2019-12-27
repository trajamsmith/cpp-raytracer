//
//  canvas.hpp
//  RayTracer
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef canvas_hpp
#define canvas_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "colors.hpp"

class Canvas {
public:
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;
    
    Canvas(int width, int height);
};

void writePixel(Canvas& canvas, int x, int y, Color color);

Color pixelAt(Canvas canvas, int x, int y);

int transformColorValue(double d);

std::string pixelToString(Color color);

void canvasToPPM(Canvas canvas);

// Demo function
void paintCannonTrajectory();

#endif /* canvas_hpp */
