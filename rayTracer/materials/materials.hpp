//
//  materials.hpp
//  RayTracer
//
//  Created by Beeb on 12/26/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef materials_hpp
#define materials_hpp

#include <stdio.h>
#include "colors.hpp"
#include "lights.hpp"

class Material {
public:
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    
    Material(Color color=Color{1, 1, 1}, double ambient=0.1,
             double diffuse=0.9, double specular=0.9,
             double shininess=200.0) : color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {};
    
    void print();
    
    bool operator== (Material m2) const;
};

Color lighting(Material m, PointLight l, Point p, Vector eyeV, Vector normalV, bool inShadow=false);

#endif /* materials_hpp */
