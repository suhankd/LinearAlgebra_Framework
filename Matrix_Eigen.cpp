#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"
#include <random>

/*

Here, I use the power iteration method to compute the most dominant eigenvalue.

*/

float Matrix::EigenValue()
{

    Matrix copyMatrix(this->numRows, this->numCols);
    copyMatrix = *this;

    if (!this->IsSquare())
    {
        throw std::invalid_argument("Cannot compute eigen-value :: Non square matrix.");
    }

    Matrix identityMatrix(this->numRows, this->numCols);
    identityMatrix.setToIdentity();

    Matrix eigenVector(this->numRows, 1);
    for (int i = 0; i < this->numRows; i++)
    {
        eigenVector.MatrixData[i][0] = randomFloat();
    }

    // Computing the Eigen-Vector using Power-Iteration method.

    int numIters = 100;
    for (int i = 0; i < numIters; i++)
    {

        eigenVector = (*this) * eigenVector;
        Normalize(eigenVector);
    }

    Matrix scaledEigvec(this->numRows, 1);
    scaledEigvec = (*this) * (eigenVector);

    float eigenValue = 0.0;

    for (int i = 0; i < this->numRows; i++)
    {
        eigenValue += (scaledEigvec.MatrixData[i][0]);
    }

    eigenValue = eigenValue / (this->numRows);
    return eigenValue;
}

float randomFloat()
{

    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

void Normalize(Matrix &Vector)
{

    float Magnitude = 0.0;
    for (int i = 0; i < Vector.numRows; i++)
    {

        Magnitude += pow(Vector.MatrixData[i][0], 2);
    }

    Magnitude = sqrt(Magnitude);

    for (int i = 0; i < Vector.numRows; i++)
    {

        Vector.MatrixData[i][0] = (Vector.MatrixData[i][0]) * (1 / Magnitude);
    }
}
