//
//  demoCannon.cpp
//  RayTracer
//
//  Created by Beeb on 12/14/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "tuples.hpp"


Projectile::Projectile(Point position, Vector velocity) : position(position), velocity(velocity) {};

Environment::Environment(Vector gravity, Vector wind) : gravity(gravity), wind(wind) {};

Projectile tick(Environment env, Projectile proj) {
    Point position = proj.position + proj.velocity;
    Vector velocity = proj.velocity + env.gravity + env.wind;
    return Projectile(position, velocity);
}

void shootCannon() {
    Projectile p = Projectile(Point(0, 1, 0), normalize(Vector(1, 1, 0)));
    Environment e = Environment(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));
    
    int i = 0;
    while (p.position.y > 0) {
        p = tick(e, p);
        std::cout << "The projectile's height is " << p.position.y << std::endl;
        i++;
    }
    std::cout << "It took " << i << " ticks to hit the ground." << std::endl;
};
