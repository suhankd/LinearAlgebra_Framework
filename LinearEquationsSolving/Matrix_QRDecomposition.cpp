#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"
#include <tuple>

/*

This method decomposes a matrix into the product of an orthogonal matrix and an upper triangular matrix. After that, easy to calculate X.
As long as a matrix is invertible, this method works.
Assuming X and B are mono-columnar for simplicity.

*/

Matrix QRSolve(Matrix &A, Matrix &B)
{

    Matrix orthoMatrix(A.numRows, A.numCols);
    Matrix triangleMatrix(A.numRows, A.numCols);

    GramSchmidtDecomposition(A, orthoMatrix, triangleMatrix);

    B = (orthoMatrix.Transpose() * B);

    Matrix X(A.numRows, 1);

    for (int i = A.numRows - 1; i > -0; i--)
    {

        float temp = 0.0;

        for (int k = i + 1; k < A.numRows; k++)
        {

            temp += ((triangleMatrix.MatrixData[i][k]) * (X.MatrixData[k][0]));
        }

        X.MatrixData[i][0] = (B.MatrixData[i][0] - temp) / triangleMatrix.MatrixData[i][i];
    }

    return X;
}

void GramSchmidtDecomposition(Matrix &A, Matrix &orthoMatix, Matrix &triangMatrix)
{

    if (!A.IsSquare())
    {
        throw std::invalid_argument("Matrix is non-square.");
    }

    // First, let us transpose A, temporarily, for ease of use
    A = A.Transpose();

    float *tempVector = new float[A.numRows];
    makeZero(tempVector, A.numRows);

    for (int rowIndex = 0; rowIndex < A.numRows; rowIndex++)
    {

        copyRow(A, rowIndex, tempVector);

        for (int k = 0; k < rowIndex; k++)
        {

            float *_ = tempVector;
            tempVector = subVectors(tempVector, scalarMul(orthoMatix.MatrixData[k], dotProduct(orthoMatix.MatrixData[k], tempVector, A.numRows), A.numRows), A.numRows);
            delete[] _;
            _ = tempVector;
        }

        Normalize(tempVector, A.numRows);
        copyVector(orthoMatix, rowIndex, tempVector);
    }

    delete[] tempVector;

    for (int i = 0; i < A.numRows; i++)
    {

        for (int j = 0; j <= i; j++)
        {

            triangMatrix.MatrixData[j][i] = dotProduct(A.MatrixData[i], orthoMatix.MatrixData[j], A.numRows);
        }
    }

    A = A.Transpose();
    triangMatrix = triangMatrix.Transpose();
    orthoMatix = orthoMatix.Transpose();
}

/*

Utility functions for vectors.

*/

float dotProduct(float *vectorA, float *vectorB, int size)
{

    float dtPrd = 0.0;
    for (int i = 0; i < size; i++)
    {

        dtPrd += (vectorA[i]) * (vectorB[i]);
    }

    return dtPrd;
}

float *scalarMul(float *vector, float scalar, int size)
{

    float *mulVector = new float[size];

    for (int i = 0; i < size; i++)
    {

        mulVector[i] = (scalar) * (vector[i]);
    }

    delete[] vector;
    return mulVector;
}

void Normalize(float *vector, int size)
{

    float magnitude = 0.0;

    for (int i = 0; i < size; i++)
    {

        magnitude += pow(vector[i], 2);
    }

    magnitude = sqrt(magnitude);

    for (int i = 0; i < size; i++)
    {

        vector[i] = (vector[i]) / magnitude;
    }
}

void copyRow(Matrix &A, int index, float *vector)
{

    for (int i = 0; i < A.numRows; i++)
    {

        vector[i] = A.MatrixData[index][i];
    }
}

void copyVector(Matrix &A, int index, float *vector)
{

    for (int i = 0; i < A.numRows; i++)
    {

        A.MatrixData[index][i] = vector[i];
    }
}

float *subVectors(float *vectorA, float *vectorB, int size)
{

    float *subbedVec = new float[size];

    for (int i = 0; i < size; i++)
    {

        subbedVec[i] = (vectorA[i] - vectorB[i]);
    }

    return subbedVec;
}

float *addVectors(float *vectorA, float *vectorB, int size)
{

    float *summedVector = new float[size];

    for (int i = 0; i < size; i++)
    {

        summedVector[i] = (vectorA[i] + vectorB[i]);
    }

    return summedVector;
}

void makeZero(float *vector, int size)
{

    for (int i = 0; i < size; i++)
    {

        vector[i] = 0.0;
    }
}