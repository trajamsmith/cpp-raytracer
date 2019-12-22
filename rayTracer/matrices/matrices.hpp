//
//  matrices.hpp
//  RayTracer
//
//  Created by Beeb on 12/20/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#ifndef matrices_hpp
#define matrices_hpp

#include <stdio.h>
#include <vector>
#include "tuples.hpp"

#endif /* matrices_hpp */

using namespace std;

class Matrix {
private:
    vector<vector<double>> data;
    
public:
    Matrix(vector<vector<double>> data);
    
    double get(int row, int col) const {
        return data[row][col];
    };
    
    void set(int row, int col, double val) {
        if (row >= height() || col >= width())
            throw "Index out of bounds";
        data[row][col] = val;
    };
    
    vector<vector<double>> read() const {
        return data;
    };
    
    int width() const {
        return int(data[0].size());
    };
    
    int height() const {
        return int(data.size());
    };
    
    void print() const;
    
    Matrix operator* (const Matrix& B);
    
    template <typename T>
    T operator* (const T& t) {
        if (this->height() != 4 || this->width() != 4) {
            throw "Only 4x4 matrices can multiply tuples";
        }
        
        vector<vector<double>> data = this->read();
        vector<double> tvals = {t.x, t.y, t.z, t.w};
        vector<double> output = {0, 0, 0, 0};
        
        for (int row = 0; row < data.size(); row++) {
            double sum = 0;
            for (int col = 0; col < data[0].size(); col++) {
                sum += data[row][col] * tvals[col];
            }
            output[row] = sum;
        }
        
        return T(output);
    };
    
    bool operator== (const Matrix& B) const;
};

Matrix initZeroMatrix(int m, int n);

Matrix transposeMatrix(const Matrix& A);

Matrix initIdentityMatrix(int m);

Matrix submatrix(const Matrix& A, int row, int col);

double minor(Matrix A, int row, int col);

double cofactor(Matrix A, int row, int col);

double determinant(Matrix A);

Matrix inverse(Matrix A);
