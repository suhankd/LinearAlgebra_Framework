#include "matrix.h"

/*

Calculating the inverse through cholesky decomposition.

*/

Matrix Matrix::CholeskyFactor() {

    Matrix choleskyFactor(numRows, numCols);
    
    for(int i = 0; i < numRows; i++) {

        for(int j = 0; j <= i; j++) {

            float temp = 0.0;

            if(i == j) {

                for(int k = 0; k < j; k++) {

                    temp += (float)pow(choleskyFactor.MatrixData[j][k],2);

                }

                choleskyFactor.MatrixData[i][i] = sqrt(MatrixData[j][j] - temp);

            } else {

                for(int k = 0; k < j; k++) {

                    temp += (choleskyFactor.MatrixData[j][k])*(choleskyFactor.MatrixData[i][k]);

                }

                choleskyFactor.MatrixData[i][j] = (MatrixData[i][j]-temp)/(choleskyFactor.MatrixData[j][j]);

            }

        }

    }

    return choleskyFactor;

}

//This function aims to return 'X' from the equality AX = B. Here, I have used LU Cholesky decomposition, and then used back-subsitution to return the
//answer.

Matrix Matrix::linearEquSol(Matrix& outputMatrix) {

    //Here, I am assuming the weight estimate is a mono-columnar matrix.

    Matrix upperTMatrix(numRows,numCols);
    Matrix lowerTMatrix(numRows, numCols);

    lowerTMatrix = this->CholeskyFactor();
    upperTMatrix = lowerTMatrix.Transpose();

    Matrix yMatrix(numRows, 1);
    Matrix xMatrix(numRows, 1);

    for(int i = 0; i < numRows; i++) {

        float temp = 0.0;

        for(int k = 0; k < i; k++) {

            temp += (lowerTMatrix.MatrixData[i][k])*yMatrix.MatrixData[k][0];

        }

        yMatrix.MatrixData[i][0] = (outputMatrix.MatrixData[i][0]-temp)/lowerTMatrix.MatrixData[i][i];

    }

    for(int i = numRows-1; i >= 0; i--) {

        float temp = 0.0;

        for(int k = i+1; k < numRows; k++) {

            temp += (upperTMatrix.MatrixData[i][k])*xMatrix.MatrixData[k][0];

        }

        xMatrix.MatrixData[i][0] = (yMatrix.MatrixData[i][0] - temp)/upperTMatrix.MatrixData[i][i];

    }

    return xMatrix;

}