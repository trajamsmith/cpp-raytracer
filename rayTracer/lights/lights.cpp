//
//  lights.cpp
//  RayTracer
//
//  Created by Beeb on 12/26/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "lights.hpp"
#include <iostream>

using namespace std;

bool PointLight::operator== (const PointLight& l2) const {
    return (this->position == l2.position &&
            this->intensity == l2.intensity);
};

void PointLight::print() {
    cout << "Position: " << endl;
    this->position.print();
    cout << "Intensity: " << endl;
    this->intensity.print();
};
