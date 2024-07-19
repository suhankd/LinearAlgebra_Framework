#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <math.h>
#include <vector>
#include <tuple>

class Matrix
{

public:
    // Defining the various constructors.
    Matrix();
    Matrix(int nRows, int nCols);
    Matrix(int nRows, int nCols, float **inputArray);
    Matrix(const Matrix &inputMatrix);

    // Define the destructor.
    ~Matrix();

    // Configuration methods.
    void Resize(int nRows, int nCols);
    void setToIdentity();
    Matrix Transpose();
    Matrix RowEchelon();

    // Determinant Calculation.
    float Determinant();

    // Overloading operators.
    bool operator==(const Matrix &rhs);
    Matrix operator=(const Matrix &rhs);

    // Overloading the '+' operator.
    friend Matrix operator+(const float &lhs, const Matrix &rhs);
    friend Matrix operator+(const Matrix &lhs, const float &rhs);
    friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);

    // Overloading the '-' operator.
    friend Matrix operator-(const float &lhs, const Matrix &rhs);
    friend Matrix operator-(const Matrix &lhs, const float &rhs);
    friend Matrix operator-(const Matrix &lhs, const Matrix &rhs);

    // Overloading the '*' operator.
    friend Matrix operator*(const float &lhs, const Matrix &rhs);
    friend Matrix operator*(const Matrix &lhs, const float &rhs);
    friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);

    // The "==" operator with some tolerance.
    bool CloseEnough(float f1, float f2);
    bool Compare(Matrix matrix2, double tolerance);

    // Overloading the '<<' operator.
    friend std::ostream &operator<<(std::ostream &COUT, const Matrix &matrixInst);

    // Cholesky Decomposition
    Matrix CholeskyFactor();

    // Gauss-Jordan inversion
    Matrix Inverse();

    // Rank calculation.
    int Rank();

    // Eigen-Functionality
    float EigenValue();

    // Gauss-Jordan configuration functions.
    void Separate(Matrix &matrix1, Matrix &matrix2, int colNum);
    void Join(Matrix &matrix2);

    Matrix SubMatrix(int rowNum, int colNum);

    void SwapRow(int i, int j);
    void MultAdd(int i, int j, float mulFactor);
    void MultRow(int i, float mulFactor);
    int FindRowWithMaxElement(int colNumber, int startingRow);

    // Simple utility functions.
    bool IsRowEchelon();
    bool IsNonZero();
    bool IsSymmetric();
    bool IsSquare();

    float **MatrixData;
    int numRows, numCols;
};

// Linear equation solving functions. I assume B is mono-columnar for simplicity.

Matrix choleskySolve(Matrix &A, Matrix &B);
Matrix inverseSolve(Matrix &A, Matrix &B);

void GramSchmidtDecomposition(Matrix &A, Matrix &orthoMatix, Matrix &triangularMatrix);
Matrix QRSolve(Matrix &A, Matrix &B);

#endif