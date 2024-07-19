#include "C:\Users\suhan\Coding_Projects\LinearAlgebraFramework\matrix.h"

/*

Initialize a stack for submatrices, and then continuously push back submatrices. 
Once we find a matrix whose determinant isn't 0, we return that matrix's dimension as the rank of the parent matrix. 

*/

int Matrix::Rank()
{

    if (!this->IsSquare())
    {
        throw std::invalid_argument("Non-square matrix. Cannot compute rank.");
    }

    std::vector<Matrix> subMatrixVector;
    subMatrixVector.push_back(*this);

    bool completeFlag = false;
    int subMatrixCount = 0;

    while (!completeFlag && subMatrixCount < subMatrixVector.size())
    {

        Matrix currentMatrix = subMatrixVector[subMatrixCount];

        if (!currentMatrix.IsNonZero())
        {

            float currDet = currentMatrix.Determinant();
            if (!CloseEnough(currDet, 0.0))
            {

                return currentMatrix.numRows;
            }
            else
            {

                if (currentMatrix.numRows > 2)
                {

                    for (int i = 0; i < currentMatrix.numRows; i++)
                    {

                        for (int j = 0; j < currentMatrix.numCols; j++)
                        {

                            subMatrixVector.push_back(currentMatrix.SubMatrix(i, j));
                            subMatrixCount++;
                        }
                    }
                }
            }
        }
    }

    return 1;
}
