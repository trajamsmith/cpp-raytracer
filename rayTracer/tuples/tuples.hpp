//
//  tuples.hpp
//  RayTracer
//
//  Created by Beeb on 12/12/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef tuples_hpp
#define tuples_hpp

#include <stdio.h>

#endif /* tuples_hpp */

// Class Declarations
class Tuple {
public:
    double x, y, z, w;
    
    Tuple(double coord_x, double coord_y, double coord_z, double coord_w);
    
    bool operator== (const Tuple& t2) const;
    
    Tuple operator+ (const Tuple& t2);
    
    Tuple operator/ (double s);
};

class Point : public Tuple {
public:
    Point(double coord_x, double coord_y, double coord_z);
    
    Point operator- (const Point& p2);
};

class Vector : public Tuple {
public:
    Vector(double coord_x, double coord_y, double coord_z);
    
    double magnitude();
};

Point addTuples(Point tuple1, Vector tuple2);
Vector addTuples(Vector tuple1, Vector tuple2);

Point subtractVectorFromPoint(Point point, Vector vector);

Vector subtractVectors(Vector vector1, Vector vector2);

Tuple negateTuple(Tuple tuple);

Tuple multiplyTuple(Tuple tuple, double scalar);
Vector multiplyTuple(Vector tuple, double scalar);

double magnitude(Vector vector);

Vector normalize(Vector vector);

double dotProduct(Tuple t1, Tuple t2);

Vector crossProduct(Vector v1, Vector v2);

// Demo
class Projectile {
public:
    Point position;
    Vector velocity;
    Projectile(Point position, Vector velocity);
};

class Environment {
public:
    Vector gravity;
    Vector wind;
    Environment(Vector gravity, Vector wind);
};

Projectile tick(Environment env, Projectile proj);

void shootCannon();
