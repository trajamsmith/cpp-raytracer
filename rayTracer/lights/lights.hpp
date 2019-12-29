//
//  lights.hpp
//  RayTracer
//
//  Created by Beeb on 12/26/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef lights_hpp
#define lights_hpp

#include <stdio.h>
#include "colors.hpp"
#include "tuples.hpp"

class PointLight {
public:
    Point position;
    Color intensity;
    
    PointLight(Point p, Color c) : position(p), intensity(c) {};
    
    void print();
    
    bool operator== (const PointLight& l2) const;
};

#endif /* lights_hpp */
