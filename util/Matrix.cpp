#include "Matrix.h"

#include <iomanip>

Matrix::Matrix()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix& mat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x[i][j] = mat.x[i][j];
        }
    }
}

void Matrix::operator = (const Matrix& mat)
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

void Matrix::inverse()
{
    double det = determinant();
    Matrix inverse;

    inverse.x[0][0] =  det3(x[1][1], x[1][2], x[1][3],
                            x[2][1], x[2][2], x[2][3],
                            x[3][1], x[3][2], x[3][3]) / det;
    inverse.x[0][1] = -det3(x[0][1], x[0][2], x[0][3], 
                            x[2][1], x[2][2], x[2][3], 
                            x[3][1], x[3][2], x[3][3]) / det;
    inverse.x[0][2] =  det3(x[0][1], x[0][2], x[0][3],
                            x[1][1], x[1][2], x[1][3], 
                            x[3][1], x[3][2], x[3][3]) / det;
    inverse.x[0][3] = -det3(x[0][1], x[0][2], x[0][3], 
                            x[1][1], x[1][2], x[1][3], 
                            x[2][1], x[2][2], x[2][3]) / det;

    inverse.x[1][0] = -det3(x[1][0], x[1][2], x[1][3], 
                            x[2][0], x[2][2], x[2][3], 
                            x[3][0], x[3][2], x[3][3]) / det;
    inverse.x[1][1] =  det3(x[0][0], x[0][2], x[0][3], 
                            x[2][0], x[2][2], x[2][3], 
                            x[3][0], x[3][2], x[3][3]) / det;
    inverse.x[1][2] = -det3(x[0][0], x[0][2], x[0][3], 
                            x[1][0], x[1][2], x[1][3], 
                            x[3][0], x[3][2], x[3][3]) / det;
    inverse.x[1][3] =  det3(x[0][0], x[0][2], x[0][3], 
                            x[1][0], x[1][2], x[1][3], 
                            x[2][0], x[2][2], x[2][3]) / det;

    inverse.x[2][0] =  det3(x[1][0], x[1][1], x[1][3], 
                            x[2][0], x[2][1], x[2][3], 
                            x[3][0], x[3][1], x[3][3]) / det;
    inverse.x[2][1] = -det3(x[0][0], x[0][1], x[0][3], 
                            x[2][0], x[2][1], x[2][3], 
                            x[3][0], x[3][1], x[3][3]) / det;
    inverse.x[2][2] =  det3(x[0][0], x[0][1], x[0][3], 
                            x[1][0], x[1][1], x[1][3], 
                            x[3][0], x[3][1], x[3][3]) / det;
    inverse.x[2][3] = -det3(x[0][0], x[0][1], x[0][3], 
                            x[1][0], x[1][1], x[1][3], 
                            x[2][0], x[2][1], x[2][3]) / det;

    inverse.x[3][0] = -det3(x[1][0], x[1][1], x[1][2], 
                            x[2][0], x[2][1], x[2][2], 
                            x[3][0], x[3][1], x[3][2]) / det;
    inverse.x[3][1] =  det3(x[0][0], x[0][1], x[0][2], 
                            x[2][0], x[2][1], x[2][2], 
                            x[3][0], x[3][1], x[3][2]) / det;
    inverse.x[3][2] = -det3(x[0][0], x[0][1], x[0][2], 
                            x[1][0], x[1][1], x[1][2], 
                            x[3][0], x[3][1], x[3][2]) / det;
    inverse.x[3][3] =  det3(x[0][0], x[0][1], x[0][2], 
                            x[1][0], x[1][1], x[1][2], 
                            x[2][0], x[2][1], x[2][2]) / det;

    *this = inverse;
}

double Matrix::determinant() const
{
    double det;
    det =  x[0][0] * det3(x[1][1], x[1][2], x[1][3],
                          x[2][1], x[2][2], x[2][3],
                          x[3][1], x[3][2], x[3][3]);
    det -= x[0][1] * det3(x[1][0], x[1][2], x[1][3], 
                          x[2][0], x[2][2], x[2][3],
                          x[3][0], x[3][2], x[3][3]);
    det += x[0][2] * det3(x[1][0], x[1][1], x[1][3], 
                          x[2][0], x[2][1], x[2][3],
                          x[3][0], x[3][1], x[3][3]);
    det -= x[0][3] * det3(x[1][0], x[1][1], x[1][2], 
                          x[2][0], x[2][1], x[2][2],
                          x[3][0], x[3][1], x[3][2]);
    return det;
}

double Matrix::det3(double a, double b, double c,
                    double d, double e, double f,
                    double g, double h, double i)
{
    return a * e * i + d * h * c + g * b * f 
         - g * e * c - d * b * i - a * h * f; 
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

