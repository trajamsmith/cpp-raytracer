//
//  colors.cpp
//  RayTracer
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "colors.hpp"
#include <math.h>
#include <iostream>

Color::Color(double r, double g, double b) : red(r), green(g), blue(b) {
};

void Color::print() {
    std::cout << "RGB: " << this->red << " | " <<
    this->green << " | " << this->blue << std::endl;
};

bool Color::operator== (const Color& c2) const {
    double e = .0001;
    double red = abs(this->red - c2.red) < e;
    double green = abs(this->green - c2.green) < e;
    double blue = abs(this->blue - c2.blue) < e;
    return (red && green && blue);
};

Color Color::operator* (const Color& c2) const {
    return Color(this->red * c2.red,
                 this->green * c2.green,
                 this->blue * c2.blue);
}

Color Color::operator* (const double& s) const {
    return Color(this->red * s,
                 this->green * s,
                 this->blue * s);
}

Color Color::operator+ (const Color& c2) const {
    return Color(this->red + c2.red,
                 this->green + c2.green,
                 this->blue + c2.blue);
};

Color Color::operator- (const Color& c2) const {
    return Color(this->red - c2.red,
                 this->green - c2.green,
                 this->blue - c2.blue);
};
