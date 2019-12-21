//
//  colors.cpp
//  RayTracer
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "colors.hpp"

Color::Color(double r, double g, double b) : red(r), green(g), blue(b) {
};

bool colorEquality(Color c1, Color c2) {
    return (c1.red == c2.red &&
            c1.green == c2.green &&
            c1.blue == c2.blue);
};

Color addColors(Color c1, Color c2) {
    return Color(c1.red + c2.red,
                 c1.green + c2.green,
                 c1.blue + c2.blue);
};

Color subtractColor(Color c1, Color c2) {
    return Color(c1.red - c2.red,
                 c1.green - c2.green,
                 c1.blue - c2.blue);
};

Color multiplyColorByScalar(Color c1, double s) {
    return Color(c1.red * s,
                 c1. green * s,
                 c1. blue * s);
};

Color multiplyColors(Color c1, Color c2) {
    return Color(c1.red * c2.red,
                 c1.green * c2.green,
                 c1.blue * c2.blue);
};
