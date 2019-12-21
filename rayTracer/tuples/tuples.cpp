//
//  tuples.cpp
//  RayTracer
//
//  Created by Beeb on 12/12/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "tuples.hpp"
#include <math.h>

// Tuples
Tuple::Tuple(double coord_x, double coord_y, double coord_z, double coord_w) {
    x = coord_x;
    y = coord_y;
    z = coord_z;
    w = coord_w;
};

bool Tuple::operator== (const Tuple& t2) const {
    return ((this->x == t2.x) &&
            (this->y == t2.y) &&
            (this->z == t2.z) &&
            (this->w == t2.w));
};

Tuple Tuple::operator+ (const Tuple& t2) {
    double x = this->x + t2.x;
    double y = this->y + t2.y;
    double z = this->z + t2.z;
    double w = this->w + t2.w;
    
    return Tuple(x, y, z, w);
};

Tuple Tuple::operator/ (double s) {
    return Tuple(this->x/s, this->y/s, this->z/s, this->w/s);
};

// Points
Point::Point(double coord_x, double coord_y, double coord_z) : Tuple(coord_x, coord_y, coord_z, 1.0) {
};

Point Point::operator- (const Point& p2) {
    double x = this->x - p2.x;
    double y = this->y - p2.y;
    double z = this->z - p2.z;
    
    return Point(x, y, z);
};

// Vectors
Vector::Vector(double coord_x, double coord_y, double coord_z) : Tuple(coord_x, coord_y, coord_z, 0.0) {
};

double Vector::magnitude() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
};

// Other
Point addTuples(Point tuple1, Vector tuple2) {
    double x = tuple1.x + tuple2.x;
    double y = tuple1.y + tuple2.y;
    double z = tuple1.z + tuple2.z;
    
    return Point(x, y, z);
};

Vector addTuples(Vector tuple1, Vector tuple2) {
    double x = tuple1.x + tuple2.x;
    double y = tuple1.y + tuple2.y;
    double z = tuple1.z + tuple2.z;
    
    return Vector(x, y, z);
};

Point subtractPoints(Point point1, Point point2) {
    double x = point1.x - point2.x;
    double y = point1.y - point2.y;
    double z = point1.z - point2.z;
    
    return Point(x, y, z);
};

Point subtractVectorFromPoint(Point point, Vector vector) {
    double x = point.x - vector.x;
    double y = point.y - vector.y;
    double z = point.z - vector.z;
    
    return Point(x, y, z);
};

Vector subtractVectors(Vector vector1, Vector vector2) {
    double x = vector1.x - vector2.x;
    double y = vector1.y - vector2.y;
    double z = vector1.z - vector2.z;
    
    return Vector(x, y, z);
};

Tuple negateTuple(Tuple tuple) {
    return Tuple(-tuple.x, -tuple.y, -tuple.z, -tuple.w);
};

Tuple multiplyTuple(Tuple tuple, double s) {
    return Tuple(s*tuple.x, s*tuple.y, s*tuple.z, s*tuple.w);
};

Vector multiplyTuple(Vector tuple, double s) {
    return Vector(s*tuple.x, s*tuple.y, s*tuple.z);
};

double magnitude(Vector vector) {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
};

Vector normalize(Vector vector) {
    // Not sure if we need to do the w coordinate here?
    // It's unclear in the textbook.
    double mag = magnitude(vector);
    return Vector(vector.x/mag, vector.y/mag, vector.z/mag);
};

double dotProduct(Tuple t1, Tuple t2) {
    return (t1.x * t2.x +
            t1.y * t2.y +
            t1.z * t2.z +
            t1.w * t2.w);
};

Vector crossProduct(Vector v1, Vector v2) {
    return Vector(v1.y * v2.z - v1.z * v2.y,
                  v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x);
};
