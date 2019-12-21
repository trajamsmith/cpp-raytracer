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
    double x;
    double y;
    double z;
    double w;
    
    Tuple(double coord_x, double coord_y, double coord_z, double coord_w);
};

class Point : public Tuple {
public:
    Point(double coord_x, double coord_y, double coord_z);
};

class Vector : public Tuple {
public:
    Vector(double coord_x, double coord_y, double coord_z);
};

// Tuple Arithmetic
bool tupleEquality(Tuple tuple1, Tuple tuple2);

Tuple addTuples(Tuple tuple1, Tuple tuple2);
Point addTuples(Point tuple1, Vector tuple2);
Vector addTuples(Vector tuple1, Vector tuple2);

Point subtractPoints(Point point1, Point point2);

Point subtractVectorFromPoint(Point point, Vector vector);

Vector subtractVectors(Vector vector1, Vector vector2);

Tuple negateTuple(Tuple tuple);

Tuple multiplyTuple(Tuple tuple, double scalar);
Vector multiplyTuple(Vector tuple, double scalar);

Tuple divideTuple(Tuple tuple, double scalar);

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
