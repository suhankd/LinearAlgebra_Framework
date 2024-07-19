#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"

/*

The inverse method, is extremely computationally heavy, and the cholesky method, while being computationally bearable, only works for positive definite matrices.
QR decomposition is computationally light and works on all invertible matrices. Therefore, I've gone with it to solve linear equations.

*/

Matrix linearSolve(Matrix &A, Matrix &B)
{

    return QRSolve(A, B);
}