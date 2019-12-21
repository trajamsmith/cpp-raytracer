//
//  canvas.cpp
//  RayTracer
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "canvas.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

using namespace std;

Canvas::Canvas(int width, int height) : width(width), height(height){
    vector<Color> initRow(width, Color(0, 0, 0));
    vector<vector<Color>> initPixMatrix(height, initRow);
    this->pixels = initPixMatrix;
};

void writePixel(Canvas& canvas, int x, int y, Color color) {
    if (x >= canvas.width || x < 0 ||
        y >= canvas.height || y < 0) {
        return;
    }
    
    canvas.pixels[y][x] = color;
};

Color pixelAt(Canvas canvas, int x, int y) {
    return canvas.pixels[y][x];
};

int transformColorValue(double d) {
    if (d > 1) return 255;
    
    if (d > 0)
        return int(round(d * 255));
        
    return 0;
}

string pixelToString(Color color) {
    return (to_string(transformColorValue(color.red)) + " " +
            to_string(transformColorValue(color.green)) + " " +
            to_string(transformColorValue(color.blue)));
}

void canvasToPPM(Canvas c) {
    ofstream file;
    file.open("canvas.ppm");
    
    // Append the PPM header
    string ppmHeader = ("P3\n" + to_string(c.width) + " " +
                        to_string(c.height) + "\n255\n");
    file << ppmHeader;
    
    // Append the PPM pixels
    for (auto row : c.pixels) {
        for (auto pixel : row) {
            file << pixelToString(pixel) << " ";
        }
        file << "\n";
    }
    
    file.close();
};

//void checkPPM(string expected) {
//    std::ifstream input("canvas.ppm");
//    std::stringstream sstr;
//
//    while(input >> sstr.rdbuf());
//
//    string s = sstr.str();
//    cout << s << endl;
//};
