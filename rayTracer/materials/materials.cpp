//
//  materials.cpp
//  RayTracer
//
//  Created by Beeb on 12/26/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "materials.hpp"
#include <math.h>
#include <iostream>

using namespace std;

bool Material::operator== (Material m2) const {
    return (this->color == m2.color &&
            this->ambient == m2.ambient &&
            this->diffuse == m2.diffuse &&
            this->specular == m2.specular &&
            this->shininess == m2.shininess);
};

void Material::print() {
    this->color.print();
    cout << "Ambient: " << this->ambient << endl;
    cout << "Diffuse: " << this->diffuse << endl;
    cout << "Specular: " << this->specular << endl;
    cout << "Shininess: " << this->shininess << endl;
};

Color lighting(Material material, PointLight light,
               Point point, Vector eyeV, Vector normalV,
               bool inShadow) {
    Color diffuse{0, 0, 0}, specular{0, 0, 0};
    
    Color effectiveColor = material.color * light.intensity;
    Vector lightV = normalize(light.position - point);
    Color ambient = effectiveColor * material.ambient;
    
    double lightDotNormal = dotProduct(lightV, normalV);
    if (lightDotNormal > 0) {
        diffuse = effectiveColor * material.diffuse * lightDotNormal;
        Vector reflectV = reflect(-lightV, normalV);
        double reflectDotEye = dotProduct(reflectV, eyeV);
        if (reflectDotEye <= 0) {
            Color specular{0, 0, 0};
        } else {
            double factor = pow(reflectDotEye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }

    if (inShadow == true) {
        return ambient;
    } else {
        return ambient + diffuse + specular;
    }
};
