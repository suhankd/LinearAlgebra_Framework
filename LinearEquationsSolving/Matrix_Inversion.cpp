#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"

/*

This method first calculates the inverse of A through Gauss-Jordan elimination. It is an iterative algorithm.
Then we calculate X, which is equal to (A^-1)*B. This method is extremely computationally heavy, however.

*/

// Method to calculate the inverse, through Gauss-Jordan elimination.

Matrix Matrix::Inverse()
{

    if (!(this->IsSquare()))
    {
        throw std::invalid_argument("Cannot invert a non-square matrix.");
    }
    int originalCols = this->numCols;

    Matrix identityMatrix(this->numRows, this->numCols);
    this->Join(identityMatrix);

    int numIters = 100;
    int cRow, cCol;
    bool completeFlag = false;

    for (int count = 0; (count < numIters) && !completeFlag; count++)
    {

        for (int diagIndex = 0; diagIndex < this->numRows; diagIndex++)
        {

            cRow = diagIndex;
            cCol = diagIndex;

            int maxIndex = FindRowWithMaxElement(cCol, cRow);
            if (maxIndex != cRow)
            {
                this->SwapRow(cRow, maxIndex);
            }

            if (this->MatrixData[cRow][cCol] != 1.0)
            {

                float mulFactor = 1.0 / (this->MatrixData[cRow][cCol]);
                this->MultRow(cRow, mulFactor);
            }

            // Column Operations

            for (int rowIndex = cRow + 1; rowIndex < this->numRows; rowIndex++)
            {

                if (!CloseEnough(this->MatrixData[rowIndex][cCol], 0.0))
                {

                    if (!CloseEnough(this->MatrixData[cCol][cCol], 0.0))
                    {

                        float correctionFactor = -(this->MatrixData[rowIndex][cCol]) / (this->MatrixData[cCol][cCol]);
                        this->MultAdd(rowIndex, cCol, correctionFactor);
                    }
                }
            }

            // Row Operations

            for (int colIndex = cCol + 1; colIndex < originalCols; colIndex++)
            {

                if (!CloseEnough(this->MatrixData[cRow][colIndex], 0.0))
                {

                    if (!CloseEnough(this->MatrixData[colIndex][colIndex], 0.0))
                    {

                        float correctionFactor = -(this->MatrixData[cRow][colIndex]) / (this->MatrixData[colIndex][colIndex]);
                        this->MultAdd(cRow, colIndex, correctionFactor);
                    }
                }
            }
        }
    }

    Matrix l;
    Matrix r;
    this->Separate(l, r, originalCols);

    if (l == identityMatrix)
    {

        completeFlag = true;

        Matrix inverseMatrix(this->numRows, originalCols);

        for (int i = 0; i < this->numRows; i++)
        {

            for (int j = 0; j < originalCols; j++)
            {

                inverseMatrix.MatrixData[i][j] = r.MatrixData[i][j];
            }
        }

        return inverseMatrix;
    }
}

Matrix inverseSolve(Matrix &A, Matrix &B)
{

    return ((A.Inverse()) * (B));
}

// Computing the Row-Echelon Form through Gaussian Elimination.

Matrix Matrix::RowEchelon()
{

    // The matrix must have atleast as many columns as rows.
    if (this->numCols < this->numRows)
    {
        throw std::invalid_argument("The matrix must have as many columns as rows.");
    }

    float **tempData = (float **)malloc(sizeof(float *) * (this->numRows));
    for (int i = 0; i < this->numRows; i++)
    {

        tempData[i] = (float *)malloc(sizeof(float) * (this->numCols));

        for (int j = 0; j < this->numCols; j++)
        {

            tempData[i][j] = this->MatrixData[i][j];
        }
    }

    int cRow, cCol;
    int numIters = 100;

    bool completeFlag = false;

    for (int count = 0; !completeFlag && (count < numIters); count++, completeFlag = this->IsRowEchelon())
    {

        for (int diagIndex = 0; diagIndex < this->numRows; diagIndex++)
        {

            cRow = diagIndex;
            cCol = diagIndex;

            int maxIndex = FindRowWithMaxElement(cRow, cCol);

            for (int rowIndex = cRow + 1; rowIndex < this->numRows; rowIndex++)
            {

                if (!CloseEnough(this->MatrixData[rowIndex][cCol], 0.0))
                {

                    if (!CloseEnough(this->MatrixData[cRow][cCol], 0.0))
                    {

                        float correctionFactor = -(this->MatrixData[rowIndex][cCol]) / (this->MatrixData[cRow][cCol]);
                        MultAdd(rowIndex, cRow, correctionFactor);
                    }
                }
            }
        }
    }

    Matrix rowEchelonForm(this->numRows, this->numCols, this->MatrixData);

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < this->numCols; j++)
        {

            this->MatrixData[i][j] = tempData[i][j];
        }

        delete[] tempData[i];
    }

    delete[] tempData;
    return rowEchelonForm;
}
