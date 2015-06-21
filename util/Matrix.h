// 4 by 4 Matrix, assume it is nonsingular.

#ifndef UTIL_MATRIX_H_
#define UTIL_MATRIX_H_

#include "Vector.h"
#include <iostream>

class Matrix
{
public:
    Matrix();
    Matrix(const Matrix& mat);
    void operator = (const Matrix& mat);

    void operator += (const Matrix& that); // M=M+M1
    friend Matrix operator + (const Matrix& m1, const Matrix& m2); // M=M1+M2

    void inverse(); // M=M^-1
    double determinant() const; // det(M)
    static double det3(double a, double b, double c,
                       double d, double e, double f,
                       double g, double h, double i);

    friend std::ostream& operator << (std::ostream& os, const Matrix& mat);

    double x[4][4];
};

#endif // UTIL_MATRIX_H_

