#include "matrix.h"

//Returns the inverse of a given matrix through Cholesky-Inversion.
// Matrix Matrix::Inverse() {

//     if(!this->isSquare()) {throw std::invalid_argument("Cannot give an inverse of a non-square matrix.");}

//     // Calculating the cholesky factors.

//     Matrix CholeskyFactor(numRows, numCols);
//     CholeskyFactor = this->CholeskyFactor();

//     Matrix IdentityMatrix(numRows, numCols);
//     IdentityMatrix.setToIdentity();

//     Matrix CholeskyInv(numRows, numCols);
    
//     for(int i = 0; i < numRows; i++) {

//         for(int j = 0; j < numRows; j++) {

//             float temp = 0.0;

//             for(int k = 0; k < i; k++) {

//                 temp += (CholeskyFactor.MatrixData[k][i] * CholeskyFactor.MatrixData[k][j]);
                
//             }

//             CholeskyInv.MatrixData[i][j] = (IdentityMatrix.MatrixData[i][j]-temp)/CholeskyFactor.MatrixData[i][i];

//         }

//     }

//     Matrix choInTra(numRows, numCols);
//     choInTra = CholeskyInv.Transpose();

//     Matrix MatrixInverse(numRows, numCols);
//     MatrixInverse = CholeskyInv * choInTra;

//     return MatrixInverse;

// }

//Returns the submatrix given a row and a column.
Matrix Matrix::FindSubMatrix(int rowNum, int colNum) {

    Matrix subMatrix(numRows-1, numCols-1);

    int count = 0;
    float * array = (float *)malloc(sizeof(float)*(numRows-1)*(numCols-1));

    for(int i = 0; i < numRows; i++) {

        for(int j = 0; j < numCols; j++) {

            if(i != rowNum && j != colNum) {

                array[count] = this->MatrixData[i][j];
                count++;
            }

        }

    }

    for(int i = 0; i < numRows-1; i++) {

        for(int j = 0; j < numCols-1; j++) {

            subMatrix.MatrixData[i][j] = array[i*(numCols-1) + j];

        }

    }

    delete array;

    return subMatrix;

}

//Returns the transpose of a matrix.
Matrix Matrix::Transpose() {

    Matrix transposedMatrix(numCols, numRows);

    float ** transposeData = (float **)malloc(sizeof(float *)*numCols);

    for(int i = 0; i < numCols; i++) {

        for(int j = 0; j < numRows; j++) {

            transposedMatrix.MatrixData[i][j] = MatrixData[j][i];

        }

    }

    return transposedMatrix;

}

//Returns the Cholesky factor (LTM) of a given matrix.
// Matrix Matrix::CholeskyFactor() {

//     if(numRows != numCols) {throw std::invalid_argument("Cholesky factor can't be obtained, as matrix isn't square.");}
//     Matrix CholeskyFactor(numRows, numRows);

//     for(int i = 0; i < numRows; i++) {

//         for(int j = 0; j <= i; j++) {

//             if(i != j) {

//                 float temp = 0.0;

//                 for(int k = 0; k < j; k++) {

//                     temp += CholeskyFactor.MatrixData[j][k] * CholeskyFactor.MatrixData[i][k];
                    
//                 }

//                 CholeskyFactor.MatrixData[i][j] = (MatrixData[i][j] - temp)/CholeskyFactor.MatrixData[j][j];
                
//             } else {

//                 float temp = 0.0;

//                 for(int k = 0; k < j; k++) {

//                     temp += pow(CholeskyFactor.MatrixData[i][k],2);
                    
//                 }

//                 CholeskyFactor.MatrixData[i][j] = sqrt(MatrixData[i][j] - temp);

//             }
            
//         }

//     }

//     return CholeskyFactor;

// };

//Calculating the determinant of an NxN matrix through recursion.
float Matrix::Determinant() {

    if(numRows != numCols) {throw std::invalid_argument("Cannot calculate the determinant of a non-square matrix.");}

    float determinant = 0;
    
    if(numRows == 2) {

        determinant = (MatrixData[0][0]*MatrixData[1][1] - MatrixData[1][0]*MatrixData[0][1]);

    } else {

        float sum = 0.0;
        float sign = 1.0;   

        for(int j = 0; j < numCols; j++) {

            Matrix subMatrix(numRows-1, numCols-1);
            subMatrix = this->FindSubMatrix(0,j);
            sum += this -> MatrixData[0][j]*subMatrix.Determinant()*sign;
            sign = -sign;

        }

        determinant = sum;

    }

    return determinant;

}
