
#ifndef EX3_PARTA_MATRIX_H
#define EX3_PARTA_MATRIX_H

#endif //EX3_PARTA_MATRIX_H
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace zich{
    class Matrix{
    public:
        std::vector<std::vector<double>> _mat;
        unsigned int _col;
        unsigned int _row;

//        Matrix(std::vector<double> &identity, int row, int col );
        Matrix(std::vector<double> identity, int row, int col );
        ~Matrix();

        friend Matrix operator + (const Matrix& a, const Matrix& b);
        friend Matrix& operator += (Matrix &a,const Matrix& b);

        friend Matrix operator - (const Matrix& a, Matrix& b);
        friend Matrix& operator -= (Matrix& a,Matrix& b);

        friend bool operator > (const Matrix& a, const Matrix& b);
        friend bool operator < (const Matrix& a, const Matrix& b);
        friend bool operator >= (const Matrix& a, const Matrix& b);
        friend bool operator <= (const Matrix& a, const Matrix& b);
        friend bool operator == (const Matrix& a, const Matrix& b);
        friend bool operator != (const Matrix& a, const Matrix& b);

        friend Matrix& operator ++ (Matrix& a ); //prefix increment
        friend Matrix& operator -- (Matrix& a );//prefix decrement
        friend Matrix operator ++ (Matrix& a, int ); //postfix increment
        friend Matrix operator -- (Matrix& a, int ); //postfix decrement

        friend Matrix operator * (const Matrix& a, const Matrix& b);
        friend Matrix operator * (const Matrix& a, double k);
        friend Matrix operator * (double k , const Matrix& a);

        friend Matrix& operator *= (double k,Matrix& a);
        friend Matrix& operator *= (Matrix& a, double k);
        friend Matrix& operator *= (Matrix& a, const Matrix& b);

        friend Matrix operator - (const Matrix& a);
        friend Matrix operator + (const Matrix& a);

        friend std::ostream& operator << (std::ostream &out,const Matrix& a);
        friend std::istream& operator>> (std::istream& is, Matrix& a);

    };

     double Matrix_sum(const Matrix& a);
     void Check_Matrix_Dim(const Matrix &a,const Matrix &b);

}

