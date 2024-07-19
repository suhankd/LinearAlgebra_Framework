#include "matrix.h"

/*
Overloading the '+' operator.
*/

Matrix operator+(const float &lhs, const Matrix &rhs)
{

    int nRows = rhs.numRows;
    int nCols = rhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < rhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < rhs.numCols; j++)
        {

            *(*(matData + i) + j) = lhs + *(*(rhs.MatrixData + i) + j);
        }
    }

    Matrix prodMatrix(nRows, nCols, matData);
    return prodMatrix;
}

Matrix operator+(const Matrix &lhs, const float &rhs)
{

    int nRows = lhs.numRows;
    int nCols = lhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < lhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < lhs.numCols; j++)
        {

            *(*(matData + i) + j) = rhs + *(*(lhs.MatrixData + i) + j);
        }
    }

    Matrix prodMatrix(nRows, nCols, matData);
    return prodMatrix;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{

    int nRows = lhs.numRows;
    int nCols = lhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < lhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < lhs.numCols; j++)
        {

            *(*(matData + i) + j) = *(*(rhs.MatrixData + i) + j) + *(*(lhs.MatrixData + i) + j);
        }
    }

    Matrix prodMatrix(nRows, nCols, matData);
    return prodMatrix;
}

/*
Overloading the '-' operator.
*/

Matrix operator-(const float &lhs, const Matrix &rhs)
{

    int nRows = rhs.numRows;
    int nCols = rhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < rhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < rhs.numCols; j++)
        {

            *(*(matData + i) + j) = lhs - *(*(rhs.MatrixData + i) + j);
        }
    }

    Matrix prodMatrix(nRows, nCols, (float **)matData);
    return prodMatrix;
}

Matrix operator-(const Matrix &lhs, const float &rhs)
{

    int nRows = lhs.numRows;
    int nCols = lhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < lhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < lhs.numCols; j++)
        {

            *(*(matData + i) + j) = *(*(lhs.MatrixData + i) + j) - rhs;
        }
    }

    Matrix prodMatrix(nRows, nCols, (float **)matData);
    return prodMatrix;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{

    int nRows = lhs.numRows;
    int nCols = lhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < lhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < lhs.numCols; j++)
        {

            *(*(matData + i) + j) = *(*(lhs.MatrixData + i) + j) - *(*(rhs.MatrixData + i) + j);
        }
    }

    Matrix prodMatrix(nRows, nCols, (float **)matData);
    return prodMatrix;
}

/*
Overloading the '*' operator.
*/

Matrix operator*(const float &lhs, const Matrix &rhs)
{

    int nRows = rhs.numRows;
    int nCols = rhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < rhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < rhs.numCols; j++)
        {

            *(*(matData + i) + j) = *(*(rhs.MatrixData + i) + j) * lhs;
        }
    }

    Matrix prodMatrix(nRows, nCols, (float **)matData);
    return prodMatrix;
}

Matrix operator*(const Matrix &lhs, const float &rhs)
{

    int nRows = lhs.numRows;
    int nCols = lhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < lhs.numRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < lhs.numCols; j++)
        {

            *(*(matData + i) + j) = *(*(lhs.MatrixData + i) + j) * rhs;
        }
    }

    Matrix prodMatrix(nRows, nCols, (float **)matData);
    return prodMatrix;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{

    if (lhs.numCols != rhs.numRows)
    {

        throw std::invalid_argument("The matrices can't be multiplied due to improper indexes.");
    }

    int nRows = lhs.numRows;
    int nCols = rhs.numCols;

    float **matData = (float **)malloc(sizeof(float *) * nRows);

    for (int i = 0; i < nRows; i++)
    {

        *(matData + i) = (float *)malloc(sizeof(float) * nCols);

        for (int j = 0; j < nCols; j++)
        {

            for (int k = 0; k < lhs.numCols; k++)
            {

                *(*(matData + i) + j) += (*(*(lhs.MatrixData + i) + k)) * (*(*(rhs.MatrixData + k) + j));
            }
        }
    }

    Matrix prodMatrix(nRows, nCols, (float **)matData);
    return prodMatrix;
}

/*
Overloading the == operator.
*/

bool Matrix::operator==(const Matrix &rhs)
{

    if ((this->numRows != rhs.numRows) || (this->numCols != rhs.numCols))
    {

        return false;
    }

    for (int i = 0; i < this->numRows; i++)
    {

        for (int j = 0; j < this->numCols; j++)
        {

            if (*(*(this->MatrixData + i) + j) != *(*(rhs.MatrixData + i) + j))
            {
                return false;
            }
        }
    }

    return true;
}

/*
Overloading the = operator.
*/

Matrix Matrix::operator=(const Matrix &rhs)
{

    if (this != &rhs)
    {

        if ((numRows == rhs.numRows) && (numCols == rhs.numCols))
        {

            for (int i = 0; i < numRows; i++)
            {

                for (int j = 0; j < numCols; j++)
                {

                    *(*(this->MatrixData + i) + j) = *(*(rhs.MatrixData + i) + j);
                }
            }
        }
        else
        {

            numRows = rhs.numRows;
            numCols = rhs.numCols;
            if (this)
            {
                delete[] this->MatrixData;
            }
            this->MatrixData = (float **)malloc(sizeof(float *) * numRows);

            for (int i = 0; i < numRows; i++)
            {

                *(this->MatrixData + i) = (float *)malloc(sizeof(float) * numCols);

                for (int j = 0; j < numCols; j++)
                {

                    *(*(this->MatrixData + i) + j) = *(*(rhs.MatrixData + i) + j);
                }
            }
        }
    }

    return *this;
}

/*
Overloading the 'cout' operator.
*/

std::ostream& operator<<(std::ostream &COUT, const Matrix &matrixInst)
{

    for (int i = 0; i < matrixInst.numRows; i++)
    {

        for (int j = 0; j < matrixInst.numCols; j++)
        {

            COUT << matrixInst.MatrixData[i][j] << " ";
        }

        COUT << "\n";
    }

    return COUT;

}

// Modified "==" functions to allow some tolerance.  

bool Matrix::CloseEnough(float f1, float f2)
{
    return fabs(f1 - f2) < 1e-9;
}

bool Matrix::Compare(Matrix matrix2, double tolerance) {

    if((matrix2.numRows != this->numRows) || (this->numCols != matrix2.numCols)) {throw std::invalid_argument("Cannot compare the matrices as they are of different shape.");}

    double cumSum = 0.0;
    for(int i = 0; i < this->numRows; i++) {

        for(int j = 0; j < this->numCols; j++) {

            cumSum += pow(this->MatrixData[i][j]-matrix2.MatrixData[i][j],2);

        }

    }
    cumSum = sqrt(cumSum/((numRows*numCols)-1));
    
    if(cumSum < tolerance) return true;
    else {return false;}

}