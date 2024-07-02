#include "matrix.h"

//Default constructor.
Matrix::Matrix()
{

    numRows = 1;
    numCols = 1;
    MatrixData = nullptr;
}

//Constructs a matrix of specified dimensions
Matrix::Matrix(int nRows, int nCols)
{

    numRows = nRows;
    numCols = nCols;
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

//Constructs a matrix of specified dimensions and data.
Matrix::Matrix(int nRows, int nCols, float **inputArray)
{

    numRows = nRows;
    numCols = nCols;
    MatrixData = (float **)malloc(sizeof(float *) * numRows);

    for (int i = 0; i < nRows; i++)
    {

        *(MatrixData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < nCols; j++)
        {

            *(*(MatrixData + i) + j) = *(*(inputArray + i) + j);
        }
    }
}

//Constructs a copy of a given matrix (passed through reference).
Matrix::Matrix(const Matrix &inputMatrix)
{

    numRows = inputMatrix.numRows;
    numCols = inputMatrix.numCols;
    MatrixData = (float **)malloc(sizeof(float *) * numRows);

    for (int i = 0; i < numRows; i++)
    {

        *(MatrixData + i) = (float *)malloc(sizeof(float) * numCols);

        for (int j = 0; j < numCols; j++)
        {

            *(*(MatrixData + i) + j) = *(*(inputMatrix.MatrixData + i) + j);
        }
    }
}

//Destructor function.
Matrix::~Matrix()
{

    if (MatrixData != nullptr)
    {

        delete[] MatrixData;
    }
}
