#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"

// Calculating the determinant of an NxN matrix through recursion.
float Matrix::Determinant()
{

    if (numRows != numCols)
    {
        throw std::invalid_argument("Cannot calculate the determinant of a non-square matrix.");
    }

    float determinant = 0;

    if (numRows == 2)
    {

        determinant = (MatrixData[0][0] * MatrixData[1][1] - MatrixData[1][0] * MatrixData[0][1]);
    }
    else
    {

        float sum = 0.0;
        float sign = 1.0;

        for (int j = 0; j < numCols; j++)
        {

            Matrix subMatrix(numRows - 1, numCols - 1);
            subMatrix = this->SubMatrix(0, j);
            sum += this->MatrixData[0][j] * subMatrix.Determinant() * sign;
            sign = -sign;
        }

        determinant = sum;
    }

    return determinant;
}
