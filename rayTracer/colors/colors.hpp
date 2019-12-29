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

class Color {
public:
    double red;
    double green;
    double blue;
    
    Color(double r, double g, double b);
    void print();
    
    bool operator== (const Color& c2) const;
    
    Color operator* (const Color& c2) const;
    Color operator* (const double& s) const;
    
    Color operator+ (const Color& c2) const;
    
    Color operator- (const Color& c2) const;
};

#endif /* colors_hpp */
