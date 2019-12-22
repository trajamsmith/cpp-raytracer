//
//  tuples.cpp
//  RayTracer
//
//  Created by Beeb on 12/12/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "tuples.hpp"
#include <math.h>
#include <vector>
#include <iostream>

// --------------- Tuples ---------------
Tuple::Tuple(double coord_x, double coord_y, double coord_z, double coord_w) {
    x = coord_x;
    y = coord_y;
    z = coord_z;
    w = coord_w;
};

Tuple::Tuple(std::vector<double> v) {
    x = v[0];
    y = v[1];
    z = v[2];
    w = v[3];
};

void Tuple::print() {
    std::cout << this->x << std::endl;
    std::cout << this->y << std::endl;
    std::cout << this->z << std::endl;
    std::cout << this->w << std::endl;
};

bool Tuple::operator== (const Tuple& t2) const {
    double e = .0001;
    double x = abs(this->x - t2.x) < e;
    double y = abs(this->y - t2.y) < e;
    double z = abs(this->z - t2.z) < e;
    double w = abs(this->w - t2.w) < e;
    return (x && y && z && w);
};

Tuple Tuple::operator- () {
    return Tuple(-this->x, -this->y, -this->z, -this->w);
};

Tuple Tuple::operator+ (const Tuple& t2) {
    double x = this->x + t2.x;
    double y = this->y + t2.y;
    double z = this->z + t2.z;
    double w = this->w + t2.w;
    
    return Tuple(x, y, z, w);
};

Tuple Tuple::operator* (double s) {
    return Tuple(s*this->x, s*this->y, s*this->z, s*this->w);
};

Tuple Tuple::operator/ (double s) {
    return Tuple(this->x/s, this->y/s, this->z/s, this->w/s);
};

// --------------- Vectors ---------------
Vector::Vector(double coord_x, double coord_y, double coord_z) : Tuple(coord_x, coord_y, coord_z, 0.0) {
};

Vector::Vector(std::vector<double> v) : Tuple(v[0], v[1], v[2], 0.0) {
};

double Vector::magnitude() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
};

Vector Vector::operator- (const Vector& v2) {
    double x = this->x - v2.x;
    double y = this->y - v2.y;
    double z = this->z - v2.z;
    
    return Vector(x, y, z);
};

Vector Vector::operator+ (const Vector& v2) {
    double x = this->x + v2.x;
    double y = this->y + v2.y;
    double z = this->z + v2.z;
    
    return Vector(x, y, z);
};

Vector Vector::operator* (double s) {
    return Vector(s*this->x, s*this->y, s*this->z);
};

// --------------- Points ---------------
Point::Point(double coord_x, double coord_y, double coord_z) : Tuple(coord_x, coord_y, coord_z, 1.0) {
};

Point::Point(std::vector<double> v) : Tuple(v[0], v[1], v[2], 1.0) {
};

Point Point::operator- (const Point& p2) {
    double x = this->x - p2.x;
    double y = this->y - p2.y;
    double z = this->z - p2.z;
    
    return Point(x, y, z);
};

Point Point::operator- (const Vector& v) {
    double x = this->x - v.x;
    double y = this->y - v.y;
    double z = this->z - v.z;
    
    return Point(x, y, z);
};

Point Point::operator+ (const Vector& v) {
    double x = this->x + v.x;
    double y = this->y + v.y;
    double z = this->z + v.z;
    
    return Point(x, y, z);
};

// --------------- Other ---------------
Vector normalize(Vector vector) {
    // Not sure if we need to do the w coordinate here?
    // It's unclear in the textbook.
    double mag = vector.magnitude();
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
