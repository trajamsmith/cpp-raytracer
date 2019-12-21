//
//  matricesTest.cpp
//  rayTracerTestRunner
//
//  Created by Beeb on 12/20/19.
//  Copyright © 2019 Beeb. All rights reserved.
//

#include "catch.hpp"
#include "matrices.hpp"

// ------------ Matrices ------------
TEST_CASE( "Constructing and inspecting a 4x4 matrix" ) {
    Matrix M = Matrix({
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    });
    REQUIRE( M.get(0,0) == 1 );
    REQUIRE( M.get(0,3) == 4 );
    REQUIRE( M.get(1,0) == 5.5 );
    REQUIRE( M.get(1,2) == 7.5 );
    REQUIRE( M.get(2,2) == 11 );
    REQUIRE( M.get(3,0) == 13.5 );
    REQUIRE( M.get(3,2) == 15.5 );
};

TEST_CASE( "A 2x2 matrix ought to be representable" ) {
    Matrix M = Matrix({
        {-3, 5},
        {1, -2}
    });
    REQUIRE( M.get(0,0) == -3 );
    REQUIRE( M.get(0,1) == 5 );
    REQUIRE( M.get(1,0) == 1 );
    REQUIRE( M.get(1,1) == -2 );
};

TEST_CASE( "A 3x3 matrix ought to be representable" ) {
    Matrix M = Matrix({
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1},
    });
    REQUIRE( M.get(0,0) == -3 );
    REQUIRE( M.get(1,1) == -2 );
    REQUIRE( M.get(2,2) == 1 );
};

TEST_CASE( "Matrix equality with identical matrices" ) {
    Matrix A = Matrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    });
    Matrix B = Matrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    });
    REQUIRE( matrixEquality(A, B) );
};

TEST_CASE( "Matrix equality with different matrices" ) {
    Matrix A = Matrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    });
    Matrix B = Matrix({
        {1, 2, 3, 4},
        {5, 6, 10, 8},
        {9, 11, 11, 12},
        {20, 14, 15, 16}
    });
    REQUIRE( !matrixEquality(A, B) );
};

TEST_CASE( "Multiplying two matrices of equal dimension" ) {
    Matrix A = Matrix({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    Matrix B = Matrix({
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    });
    Matrix mult = A * B;
    Matrix expected = Matrix({
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    });
    REQUIRE( matrixEquality(mult, expected) );
};

TEST_CASE( "Multiplying two matrices with different dimensions" ) {
    Matrix A = Matrix({
        {-2, 1, 2},
        {3, 2, 1},
    });
    Matrix B = Matrix({
        {1, 2},
        {5, 6},
        {9, 8},
    });
    Matrix mult = A * B;
    Matrix expected = Matrix({
        {21, 18},
        {22, 26},
    });
    REQUIRE( matrixEquality(mult, expected) );
};

TEST_CASE( "A matrix multiplied by a tuple" ) {
    Matrix A = Matrix({
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1},
    });
    Tuple t = Tuple(1, 2, 3, 1);
    Tuple mult = multTupleByMatrix(t, A);
    Tuple expected = Tuple(18, 24, 33, 1);
    REQUIRE( tupleEquality(mult, expected) );
}

TEST_CASE( "Multiplying a matrix by the identity matrix" ) {
    Matrix A = Matrix({
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32},
    });
    Matrix identity = initIdentityMatrix(4);
    Matrix mult = A * identity;
    REQUIRE( matrixEquality(A, mult) );
}

TEST_CASE( "Transpose a matrix" ) {
    Matrix A = Matrix({
        {-2, 1, 2},
        {3, 2, 1},
    });
    Matrix At = transposeMatrix(A);
    Matrix expected = Matrix({
        {-2, 3},
        {1, 2},
        {2, 1},
    });
    REQUIRE( matrixEquality(At, expected) == true );
}

TEST_CASE( "Transpose a square matrix" ) {
    Matrix A = Matrix({
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8},
    });
    Matrix expected = Matrix({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8},
    });
    Matrix At = transposeMatrix(A);
    REQUIRE( matrixEquality(expected, At) );
}

TEST_CASE( "Calculate the determinant of a 2x2 matrix" ) {
    Matrix A = Matrix({
        {1, 5},
        {-3, 2},
    });
    REQUIRE( determinant(A) == 17 );
}

TEST_CASE( "A submatrix of a 3x3 matrix is a 2x2 matrix" ) {
    Matrix A = Matrix({
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3},
    });
    Matrix sub = submatrix(A, 0, 2);
    Matrix expected = Matrix({
        {-3, 2},
        {0, 6},
    });
    REQUIRE( matrixEquality(sub, expected) );
}

TEST_CASE( "A submatrix of a 4x4 matrix is a 3x3 matrix" ) {
    Matrix A = Matrix({
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1},
    });
    Matrix sub = submatrix(A, 2, 1);
    Matrix expected = Matrix({
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1},
    });
    REQUIRE( matrixEquality(sub, expected) );
}

TEST_CASE( "Calculating a minor of a 3x3 matrix" ) {
    Matrix A = Matrix({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    });
    Matrix B = submatrix(A, 1, 0);
    REQUIRE( determinant(B) == 25 );
    REQUIRE( minor(A, 1, 0) == 25 );
}

TEST_CASE( "Calculating the cofactor of a 3x3 matrix" ) {
    Matrix A = Matrix({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    });
    REQUIRE( minor(A, 0, 0) == -12 );
    REQUIRE( cofactor(A, 0, 0) == -12 );
    REQUIRE( minor(A, 1, 0) == 25 );
    REQUIRE( cofactor(A, 1, 0) == -25 );
}

TEST_CASE( "Calculating the determinant of a 3x3 matrix" ) {
    Matrix A = Matrix({
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4},
    });
    REQUIRE( cofactor(A, 0, 0) == 56 );
    REQUIRE( cofactor(A, 0, 1) == 12 );
    REQUIRE( cofactor(A, 0, 2) == -46 );
    REQUIRE( determinant(A) == -196 );
}

TEST_CASE( "Calculating the determinant of a 4x4 matrix" ) {
    Matrix A = Matrix({
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9},
    });
    REQUIRE( cofactor(A, 0, 0) == 690 );
    REQUIRE( cofactor(A, 0, 1) == 447 );
    REQUIRE( cofactor(A, 0, 2) == 210 );
    REQUIRE( cofactor(A, 0, 3) == 51 );
    REQUIRE( determinant(A) == -4071 );
}

TEST_CASE( "Calculating the inverse of a matrix" ) {
    Matrix A = Matrix({
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4},
    });
    Matrix B = inverse(A);
    REQUIRE( determinant(A) == 532 );
    REQUIRE( cofactor(A, 2, 3) == -160 );
    REQUIRE( B.get(3, 2) == (-160.0/532.0) );
    REQUIRE( cofactor(A, 3, 2) == 105 );
    REQUIRE( B.get(2, 3) == (105.0/532.0) );
    Matrix expected = Matrix({
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}
    });
    REQUIRE( matrixEquality(B, expected, true) );
}

TEST_CASE( "Calculating the inverse of another matrix" ) {
    Matrix A = Matrix({
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4},
    });
    Matrix expected = Matrix({
        { -0.15385, -0.15383, -0.28205, -0.53846},
        { -0.07692, 0.12308, 0.02564, 0.03077},
        { 0.35897, 0.35897, 0.43590, 0.92308},
        { -0.69231, -0.69231, -0.76923, -1.92308},
    });
    REQUIRE( matrixEquality(inverse(A), expected, true) );
}

TEST_CASE( "Calculating the inverse of a third matrix" ) {
    Matrix A = Matrix({
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2},
    });
    Matrix expected = Matrix({
        { -0.04074, -0.07778, 0.14444, -0.22222},
        { -0.07778, 0.03333, 0.36667, -0.33333},
        { -0.02901, -0.14630, -0.10926, 0.12963},
        { 0.17778, 0.06667, -0.26667, 0.33333},
    });
    REQUIRE( matrixEquality(inverse(A), expected, true) );
}

TEST_CASE( "Multiplying a product by its inverse" ) {
    Matrix A = Matrix({
        { 3, -9, 7, 3 },
        { 3, -8, 2, -9 },
        { -4, 4, 4, 1 },
        { -6, 5, -1, 1},
    });
    Matrix B = Matrix({
        { 8, 2, 2, 2 },
        { 3, -1, 7, 0 },
        { 7, 0, 5, 4 },
        {6, -2, 0, 5 },
    });
    Matrix C = A * B;
    REQUIRE( matrixEquality(A, C * inverse(B), true) );
}
