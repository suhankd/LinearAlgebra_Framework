#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"

/*

This method consists of Cholesky factorization, and then LU-Decomposition.

*/

// Returns a lower-triangular cholesky factor.

Matrix Matrix::CholeskyFactor()
{

    Matrix choleskyFactor(numRows, numCols);

    for (int i = 0; i < numRows; i++)
    {

        for (int j = 0; j <= i; j++)
        {

            float temp = 0.0;

            if (i == j)
            {

                for (int k = 0; k < j; k++)
                {

                    temp += (float)pow(choleskyFactor.MatrixData[j][k], 2);
                }

                choleskyFactor.MatrixData[i][i] = sqrt(MatrixData[j][j] - temp);
            }
            else
            {

                for (int k = 0; k < j; k++)
                {

                    temp += (choleskyFactor.MatrixData[j][k]) * (choleskyFactor.MatrixData[i][k]);
                }

                choleskyFactor.MatrixData[i][j] = (MatrixData[i][j] - temp) / (choleskyFactor.MatrixData[j][j]);
            }
        }
    }

    return choleskyFactor;
}

Matrix choleskySolve(Matrix &A, Matrix &B)
{

    Matrix upperTMatrix(A.numRows, A.numCols);
    Matrix lowerTMatrix(A.numRows, A.numCols);

    lowerTMatrix = A.CholeskyFactor();
    upperTMatrix = lowerTMatrix.Transpose();

    Matrix yMatrix(A.numRows, 1);
    Matrix xMatrix(A.numRows, 1);

    for (int i = 0; i < A.numRows; i++)
    {

        float temp = 0.0;

        for (int k = 0; k < i; k++)
        {

            temp += (lowerTMatrix.MatrixData[i][k]) * yMatrix.MatrixData[k][0];
        }

        yMatrix.MatrixData[i][0] = (B.MatrixData[i][0] - temp) / lowerTMatrix.MatrixData[i][i];
    }

    for (int i = A.numRows - 1; i >= 0; i--)
    {

        float temp = 0.0;

        for (int k = i + 1; k < A.numRows; k++)
        {

            temp += (upperTMatrix.MatrixData[i][k]) * xMatrix.MatrixData[k][0];
        }

        xMatrix.MatrixData[i][0] = (yMatrix.MatrixData[i][0] - temp) / upperTMatrix.MatrixData[i][i];
    }

    return xMatrix;
}
