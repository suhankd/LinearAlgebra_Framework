#include "matrix.h"

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


//A function that converts the matrix to an identity matrix.
void Matrix::setToIdentity()
{

    if (!isSquare())
    {
        throw std::invalid_argument("Not a square matrix! Cannot be set to identity.");
    }

    for (int i = 0; i < numRows; i++)
    {

        for (int j = 0; j < numCols; j++)
        {

            if (i == j)
            {

                *(*(MatrixData + i) + j) = 1.0;
            }
            else
            {

                *(*(MatrixData + i) + j) = 0.0;
            }

        }

    }

}

//Self-Explanatory.
bool Matrix::isSquare()
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