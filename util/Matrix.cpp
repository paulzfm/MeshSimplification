#include "Matrix.h"
#include <iomanip>

Matrix::Matrix(const Matrix& mat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x[i][j] = mat.x[i][j];
        }
    }
}

Matrix operator + (const Matrix& m1, const Matrix& m2)
{
    Matrix mat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.x[i][j] = m1.x[i][j] + m2.x[i][j];
        }
    }
    return mat;
}

void Matrix::operator += (const Matrix& that)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->x[i][j] += that.x[i][j];
        }
    }
}

std::ostream& operator << (std::ostream& os, const Matrix& mat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << std::setprecision(3) << std::setw(8) << mat.x[i][j];
        }
        os << std::endl;
    }

    return os;
}

