#include "matrix.h"

/*

Common Configuration functions.

*/

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

// A function that converts the matrix to an identity matrix.
void Matrix::setToIdentity()
{

    if (!IsSquare())
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

// Returns the transpose of a matrix.
Matrix Matrix::Transpose()
{

    Matrix transposedMatrix(numCols, numRows);

    float **transposeData = (float **)malloc(sizeof(float *) * numCols);

    for (int i = 0; i < numCols; i++)
    {

        for (int j = 0; j < numRows; j++)
        {

            transposedMatrix.MatrixData[i][j] = MatrixData[j][i];
        }
    }

    return transposedMatrix;
}

/*

Configuration functions used in Gaussian Elimination.

*/

int Matrix::FindRowWithMaxElement(int colNumber, int startingRow)
{

    float temp = this->MatrixData[startingRow][colNumber];
    int rowIndex = startingRow;

    for (int k = startingRow + 1; k < this->numRows; k++)
    {

        if (fabs(this->MatrixData[k][colNumber]) > fabs(temp))
        {

            rowIndex = k;
            temp = this->MatrixData[k][colNumber];
        }
    }
}

void Matrix::SwapRow(int i, int j)
{

    float *_ = this->MatrixData[i];
    this->MatrixData[i] = this->MatrixData[j];
    this->MatrixData[j] = _;
}

// Function to add a multiple of row j to row i.
void Matrix::MultAdd(int i, int j, float mulFactor)
{

    for (int k = 0; k < this->numCols; k++)
    {

        this->MatrixData[i][k] += (this->MatrixData[j][k]) * mulFactor;
    }
}

void Matrix::MultRow(int i, float mulFactor)
{

    for (int k = 0; k < this->numCols; k++)
    {
        this->MatrixData[i][k] = mulFactor * (this->MatrixData[i][k]);
    }
}

void Matrix::Separate(Matrix &matrix1, Matrix &matrix2, int colNum)
{

    int numCols1 = colNum;
    int numCols2 = this->numCols - colNum;

    matrix1.Resize(this->numRows, numCols1);
    matrix2.Resize(this->numRows, numCols2);

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < this->numCols; i++)
        {

            if (j < colNum)
            {

                matrix1.MatrixData[i][j] = this->MatrixData[i][j];
            }
            else
            {

                matrix2.MatrixData[i][j - colNum] = this->MatrixData[i][j];
            }
        }
    }
}

void Matrix::Join(Matrix &matrix)
{

    if (matrix.numRows != this->numRows)
    {
        throw std::invalid_argument("Cannot join matrices, due to different column sizes.");
    }

    float **newMatrix = (float **)malloc(sizeof(float *) * (this->numRows));

    int n_Rows = this->numRows;
    int n_Cols = this->numCols + matrix.numCols;

    for (int i = 0; i < n_Rows; i++)
    {

        newMatrix[i] = (float *)malloc(sizeof(float) * (n_Cols));

        for (int j = 0; j < n_Cols; j++)
        {

            if (j < this->numCols)
            {

                newMatrix[i][j] = this->MatrixData[i][j];
            }
            else
            {

                newMatrix[i][j] = matrix.MatrixData[i][j - this->numCols];
            }
        }
    }

    for (int i = 0; i < this->numRows; i++)
    {
        delete[] this->MatrixData[i];
    }
    this->MatrixData = newMatrix;
    this->numRows = n_Rows;
    this->numCols = n_Cols;
}

/*

Configuration functions for determinant/rank calculation.

*/

Matrix Matrix::SubMatrix(int rowNum, int colNum)
{

    float *data = (float *)malloc(sizeof(float) * ((this->numCols - 1) * (this->numRows - 1)));
    int count = 0;

    Matrix subMatrix(this->numRows - 1, this->numCols - 1);

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < this->numCols; j++)
        {

            if (j != colNum && i != rowNum)
            {
                data[count] = this->MatrixData[i][j];
            }
            count++;
        }
    }

    for (int i = 0, count = 0; i < this->numRows - 1; i++)
    {

        for (int j = 0; j < this->numCols - 1; j++)
        {

            subMatrix.MatrixData[i][j] = data[count];
            count++;
        }
    }

    return subMatrix;
}
