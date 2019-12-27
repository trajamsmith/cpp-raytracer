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
#include <vector>

class Tuple {
public:
    double x, y, z, w;
    
    Tuple(double coord_x, double coord_y, double coord_z, double coord_w);
    Tuple(std::vector<double> v);
    
    void print();
    
    bool operator== (const Tuple& t2) const;
    
    Tuple operator-();
    
    Tuple operator+ (const Tuple& t2);
    
    Tuple operator* (double s);
    
    Tuple operator/ (double s);
};

class Vector : public Tuple {
public:
    Vector(double coord_x, double coord_y, double coord_z);
    Vector(std::vector<double> v);
    
    double magnitude();
    
    Vector operator- (const Vector& v2);
    Vector operator-();
    
    Vector operator+ (const Vector& v2);
    
    Vector operator* (double s);
};

class Point : public Tuple {
public:
    Point(double coord_x, double coord_y, double coord_z);
    Point(std::vector<double> v);
    
    Vector operator- (const Point& p2);
    Point operator- (const Vector& v);
    
    Point operator+ (const Vector& v);
};

Vector normalize(Vector vector);

double dotProduct(Tuple t1, Tuple t2);

Vector crossProduct(Vector v1, Vector v2);

Vector reflect(Vector v, Vector norm);

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

#endif /* tuples_hpp */
