#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <math.h>

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

    // Manipulation Methods.
    Matrix linearEquSol(Matrix& outputMatrix);
    Matrix FindSubMatrix(int rowNum, int colNum);
    Matrix Transpose();
    Matrix CholeskyFactor();

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

    // Overloading the '<<' operator.
    friend std::ostream& operator<<(std::ostream &COUT, const Matrix &matrixInst);

    bool isSquare();
    float ** MatrixData;
    int numRows, numCols;

};

#endif