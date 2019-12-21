//
//  matrices.cpp
//  RayTracer
//
//  Created by Beeb on 12/20/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "matrices.hpp"

Matrix::Matrix(vector<vector<double>> data) : data(data) {};

void Matrix::print() const {
    vector<vector<double>> data = this->data;
    
    for (auto row : data) {
        string srow = "";
        for (auto el : row) {
            srow += to_string(el) + " ";
        }
        cout << srow << endl;
    }
};

Matrix Matrix::operator* (const Matrix& B) {
    if (this->width() != B.height()) {
        throw "Matrix dimensions incompatible.";
    }
    
    Matrix output = initZeroMatrix(this->height(), B.width());
    Matrix Bt = transposeMatrix(B);
    for (int orow = 0; orow < this->height(); orow++) {
        // Per row in A
        for (int ocol = 0; ocol < B.width(); ocol++) {
            // Per row in B transpose
            double sum = 0;
            for (int i = 0; i < this->width(); i++) {
                // Per element in the rows
                sum += this->get(orow, i) * Bt.get(ocol, i);
            }
            output.data[orow][ocol] = sum;
        }
    }
    
    return output;
};

bool Matrix::operator== (const Matrix& B) const {
    if (this->read() == B.read())
        return true;
    
    if (this->height() != B.height() ||
        this->width() != B.width())
        return false;
        
    double e = .0001;
    for (int row = 0; row < this->height(); row++) {
        for (int col = 0; col < this->width(); col++) {
            double diff = abs(this->get(row, col) - B.get(row, col));
            if (diff > e)
                return false;
        }
    }
    
    return true;
};

bool matrixEquality(const Matrix& A, const Matrix& B, bool precision) {
    // For comparing floats
    if (precision) {
        if (A.height() != B.height() ||
            A.width() != B.width())
            return false;
            
        double e = .0001;
        for (int row = 0; row < A.height(); row++) {
            for (int col = 0; col < A.width(); col++) {
                double diff = abs(A.get(row, col) - B.get(row, col));
                if (diff > e)
                    return false;
            }
        }
        
        return true;
    }
    
    // Discrete-valued matrices
    return A.read() == B.read();
};

Matrix initZeroMatrix(int m, int n) {
    vector<double> row(n, 0.0);
    vector<vector<double>> array2d(m, row);
    return Matrix(array2d);
};

Matrix transposeMatrix(const Matrix& A) {
    Matrix At = initZeroMatrix(A.width(), A.height());
    
    for (int row = 0; row < A.height(); row++) {
        for (int col = 0; col < A.width(); col++) {
            At.set(col, row, A.get(row, col));
        }
    }
    
    return At;
};

Matrix tupleTo1DMatrix(Tuple t) {
    return Matrix({
        {t.x},
        {t.y},
        {t.z},
        {t.w},
    });
};

Tuple oneDMatrixToTuple(Matrix A) {
    return Tuple(A.get(0, 0), A.get(1, 0),
                 A.get(2, 0), A.get(3, 0));
};

Tuple multTupleByMatrix(Tuple t, Matrix A) {
    Matrix prod = A * tupleTo1DMatrix(t);
    return oneDMatrixToTuple(prod);
};

Matrix initIdentityMatrix(int m) {
    Matrix output = initZeroMatrix(m, m);
    
    for (int i = 0; i < m; i++) {
        output.set(i, i, 1);
    }
    
    return output;
};

Matrix submatrix(const Matrix& A, int row, int col) {
    if (row >= A.height() || col >= A.width()) {
        throw "Row or col value out of bounds";
    }
    
    vector<vector<double>> output = A.read();
    output.erase(output.begin() + row);
    for (auto& row : output) {
        row.erase(row.begin() + col);
    }
    
    return Matrix(output);
};

double minor(Matrix A, int row, int col) {
    Matrix sub = submatrix(A, row, col);
    return determinant(sub);
};

double cofactor(Matrix A, int row, int col) {
    double min = minor(A, row, col);
    bool isPos = (row + col) % 2 == 0;
    return isPos ? min : -1 * min;
};

double determinant(Matrix A) {
    if (A.height() != A.width()) {
        throw "Can't take the determinant of a non-square matrix";
    }
    
    double det = 0;
    if (A.height() == 2) {
        det = A.get(0,0) * A.get(1,1) - A.get(0,1) * A.get(1,0);
    } else {
        for (int col = 0; col < A.width(); col++) {
            det += A.get(0, col) * cofactor(A, 0, col);
        }
    }
    
    return det;
};

Matrix inverse(Matrix A) {
    double det = determinant(A);
    if (det == 0) throw "The matrix is not invertible";
    
    Matrix output = initZeroMatrix(A.height(), A.width());
    for (int row = 0; row < A.height(); row++) {
        for (int col = 0; col < A.width(); col++) {
            double c = cofactor(A, row, col);
            output.set(col, row, (c/det));
        }
    }
    
    return output;
};
