#include "matrix.h"

/*

Some simple utility functions.

*/

bool Matrix::IsSquare()
{

    if (this->numCols == this->numRows)
    {

        return true;
    }
    else
    {

        return false;
    }
}

bool Matrix::IsNonZero()
{
    int numNonZero = 0;

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < this->numCols; j++)
        {

            if (CloseEnough(this->MatrixData[i][j], 0.0))
            {
                numNonZero++;
            }
        }
    }

    return (numNonZero == 0);
}

bool Matrix::IsRowEchelon()
{

    float cumulativeSum = 0.0;

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < i; i++)
        {

            cumulativeSum += this->MatrixData[i][j];
        }
    }

    return CloseEnough(cumulativeSum, 0.0);
}

bool Matrix::IsSymmetric()
{

    if (!(this->IsSquare()))
    {
        return false;
    }

    bool returnFlag = true;

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < i; j++)
        {

            if (!CloseEnough(this->MatrixData[i][j], this->MatrixData[j][i]))
            {
                returnFlag = false;
            }
        }
    }

    return returnFlag;
}

// A function to resize the matrix to a specified number of rows and columns.
void Matrix::Resize(int nRows, int nCols)
{

    numRows = nRows;
    numCols = nCols;

    delete[] MatrixData;
    MatrixData = (float **)malloc(sizeof(float *) * numRows);

    for (int i = 0; i < numRows; i++)
    {

        *(MatrixData + i) = (float *)malloc(sizeof(float) * numCols);

        for (int j = 0; j < numCols; j++)
        {

            *(*(MatrixData + i) + j) = 0.0;
        }
    }
}


/*

Vector Utility Functions (Used in QR Decomposition).

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