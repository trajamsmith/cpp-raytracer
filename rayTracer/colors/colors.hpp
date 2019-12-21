//
//  colors.hpp
//  RayTracer
//
//  Created by Beeb on 12/17/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef colors_hpp
#define colors_hpp

#include <stdio.h>

#endif /* colors_hpp */

class Color {
public:
    double red;
    double green;
    double blue;
    
    Color(double r, double g, double b);
};

bool colorEquality(Color c1, Color c2);

Color addColors(Color c1, Color c2);

Color subtractColor(Color c1, Color c2);

Color multiplyColorByScalar(Color c, double s);

Color multiplyColors(Color c1, Color c2);
