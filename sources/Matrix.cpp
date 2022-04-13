#include <iostream>
#include "Matrix.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>

const int MINVAL=48;
const int MAXVAL=57;


using namespace std;

namespace zich {
    //private functions:
    double Matrix_sum(const Matrix& a){
        double sum=0;
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                sum+=a._mat.at(i).at(j);
            }
        }
        return sum;
    }


    void Check_Matrix_Dim(const Matrix &a,const Matrix &b) {
        if (a._col < 1 || b._col < 1 || a._row < 1 || b._row < 1) {
            throw std::invalid_argument("The dimensions of the matrices must be a positive number");
        }
        if ((a._col != b._col) || (a._row != b._row)) {
            throw std::invalid_argument("The sizes of the two matrices should be exactly equal!");
        }
    }

    //constructor
    Matrix::Matrix(std::vector<double> identity, int row, int col) {
        if (identity.size()!= row*col){
            throw std::invalid_argument("Error: The size of identity has to be equal to row*col");
        }
        if (col < 1 || row < 1) {
            throw std::invalid_argument("The dimensions of the matrices must be a positive number");
        }

        this->_row= (unsigned int) row;
        this->_col=(unsigned int) col;
        for (unsigned int i = 0; i < this->_row ; ++i) {
            std::vector<double> temp;
            temp.resize(this->_col) ;
            for (unsigned int j = 0; j <this->_col ; ++j) {
                temp.at(j)=identity.at((this->_col * i)+ j);
            }
            this->_mat.push_back(temp);
        }
    }
    //destructor
    Matrix::~Matrix(){}


    Matrix operator + (const Matrix &a,const Matrix &b) {
        if (a._col<1 || b._col<1 || a._row<1 || b._row<1 ){
            throw std::invalid_argument("The dimensions of the matrices must be a positive number");
        }
        if ((a._col!=b._col) || (a._row != b._row)){
            throw std::invalid_argument("The sizes of the two matrices should be exactly equal!");
        }
        std::vector<double> temp;
        temp.resize(a._row * a._col);
        for (unsigned int i = 0; i < a._row ; ++i) {
            for (unsigned int j = 0; j < a._col; ++j) {
                temp.at(a._col*i+j)=a._mat.at(i).at(j)+b._mat.at(i).at(j);
            }
        }
        Matrix ans {temp,(int)a._row,(int)a._col};
        return ans;
    }

    Matrix& operator += (Matrix &a,const Matrix &b) {
        Check_Matrix_Dim(a,b);
        Matrix c= a+b;
        a._mat=c._mat;
        return a;
    }

    Matrix operator - (const Matrix &a,Matrix &b){
        Check_Matrix_Dim(a,b);
        Matrix c= -b;
        Matrix ans= a + c;
        return ans;
    }

    Matrix& operator -= (Matrix &a,Matrix &b){
        Check_Matrix_Dim(a,b);
        Matrix c = a-b;
        a._mat=c._mat;
        return a;
    }

    bool operator > (const Matrix &a , const Matrix &b){
        Check_Matrix_Dim(a,b);
        double sum_a=Matrix_sum(a);
        double sum_b=Matrix_sum(b);
        return sum_a>sum_b;
    }

    bool operator < (const Matrix &a , const Matrix &b){
        Check_Matrix_Dim(a,b);
        bool isSmall= !(a>=b);
        return isSmall;
    }

    bool operator >= (const Matrix &a , const Matrix &b) {
        Check_Matrix_Dim(a,b);
        double sum_a=Matrix_sum(a);
        double sum_b=Matrix_sum(b);
        return sum_a>=sum_b;
    }

    bool operator <= (const Matrix &a , const Matrix &b) {
        Check_Matrix_Dim(a,b);
        bool isSmallEqual= !(a>b);
        return isSmallEqual;
    }

    bool operator == (const Matrix &a , const Matrix &b) {
        if (a._col<1 || b._col<1 || a._row<1 || b._row<1 ){
            throw std::invalid_argument("The dimensions of the matrices must be a positive number");
        }
        if ((a._col!=b._col) || (a._row != b._row)){
            throw std::invalid_argument("The sizes of the two matrices should be exactly equal!");
        }
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                if ( a._mat.at(i).at(j) != b._mat.at(i).at(j)){
                    return false;
                }
            }
        }
            return true;
    }




    bool operator != (const Matrix &a , const Matrix &b) {
        return !(a==b);
    }

    Matrix& operator ++ (Matrix &a) {
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                a._mat.at(i).at(j)++;
            }
        }
        return a;
    }

    Matrix& operator -- (Matrix &a) {
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                a._mat.at(i).at(j)--;
            }
        }
        return a;
    }

    Matrix operator ++ (Matrix &a, int ) {
        Matrix ans=+a;
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                a._mat.at(i).at(j)++;
            }
        }
        return ans;
    }

    Matrix operator -- (Matrix &a, int ) {
        Matrix ans = +a;
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                a._mat.at(i).at(j)--;
            }
        }
        return ans;
    }

    Matrix operator * (const Matrix &a, const Matrix &b) {
        if (a._col!=b._row){
            throw std::invalid_argument("Matrices cannot be multiplied by the number of columns of A different from the number of rows of B");
        }
        std::vector<double> temp;
        temp.resize(a._row * b._col);
        for (unsigned int i = 0; i <a._row ; ++i) {
            for (unsigned int j = 0; j <b._col ; ++j) {
                temp.at((b._col*i) + j ) = 0;
                for (unsigned int k = 0; k <a._col ; ++k) {
                    temp.at((b._col*i) + j ) += a._mat.at(i).at(k) * b._mat.at(k).at(j);
                }
            }
        }
        Matrix ans{temp,(int)a._row,(int)b._col};
        return ans;
    }

    Matrix operator * (const Matrix &a,double k){
        Matrix ans = k*a;
        return ans;
    }

    Matrix operator * (double k,const Matrix &a){
        std::vector<double> temp;
        temp.resize(a._row * a._col);
        for (unsigned int i = 0; i < a._row ; ++i) {
            for (unsigned int j = 0; j < a._col ; ++j) {
                temp.at(a._col*i+j)=a._mat.at(i).at(j) * k;
            }
        }
        Matrix ans {temp, (int)a._row, (int)a._col};
        return ans;
    }

    Matrix& operator *= (Matrix &a, double k){
        Matrix temp = a*k;
        a._mat=temp._mat;
        return a;
    }

    Matrix& operator *= (double k, Matrix &a){
        Matrix temp = a*k;
        a._mat=temp._mat;
        return a;
    }

    Matrix& operator *= (Matrix &a,const Matrix &b){
        Matrix temp = a*b;
        a._mat=temp._mat;
        a._row=temp._row;
        a._col=temp._col;
        return a;
    }

    Matrix operator - (const Matrix &a){
        std::vector<double> negative_a;
        negative_a.resize(a._row * a._col );
        for (unsigned int i = 0; i < a._row ; ++i) {
            for (unsigned int j = 0; j < a._col ; ++j) {
                negative_a.at(a._col*i+j)= a._mat.at(i).at(j) * -1;
            }
        }
        Matrix ans{negative_a,(int)a._row,(int)a._col};
        return ans;
    }

    Matrix operator + (const Matrix &a){
        std::vector<double> copy_a;
        copy_a.resize(a._col * a._row);
        for (unsigned int i = 0; i < a._row ; ++i) {
            for (unsigned int j = 0; j <a._col ; ++j) {
                copy_a.at(a._col*i+j)=a._mat.at(i).at(j);
            }
        }
        Matrix ans{copy_a,(int)a._row,(int)a._col};
        return ans;
    }

    std::ostream& operator << (std::ostream &out,const Matrix &a){
        for (unsigned int i = 0; i <a._row ; ++i) {
            out<<"[";
            for (unsigned int j = 0; j <a._col ; ++j) {
                out<<a._mat.at(i).at(j);
                if (j!=a._col-1){
                    out<<" ";
                }
                else if(j==a._col-1 && i!=a._row-1){
                    out<<"]\n";
                }else{
                    out<<"]";
                }
            }
        }
        return out;
    }

    std::istream& operator>> (std::istream& is, Matrix &a){
        int row =0;
        int col=0;
        string temp;
        vector<double> mat_a;
        while(!is.eof()){
            string substring;
            is>>substring;
            if (substring[0]=='['){
                if (substring[1]<MINVAL || substring[1]>MAXVAL){
                    throw std::invalid_argument("Invalid Matrix was entered\n");
                }
            }
            else if(substring[1]==']'){
                if (substring[2]==0){}// end of temp;
                else{
                    if(substring[2] != ',' ){
                        throw std::invalid_argument("Invalid Matrix was entered\n");
                    }
                    if(substring[3] != 0){
                        throw std::invalid_argument("Invalid Matrix was entered\n");
                    }
                }
            }
            temp+=substring;
        }
        cout<<temp<<endl;
        for (unsigned int i = 0; i <temp.length() ; ++i) {
            if (temp[i]!= '['){
                throw std::invalid_argument("Invalid Matrix was entered\n");
            }
            i++;
            row++;
            while (temp[i]!=']'){
                if(temp[i] < MINVAL || temp[i] > MAXVAL){
                    throw std::invalid_argument("Invalid Matrix was entered\n");
                }
                string value;
                value+=temp[i];
                mat_a.push_back(stod(value));
                i++;
            }
            i++;
            if (temp[i] == '\0'){
                break;
            }
            if (temp[i] != ','){
                throw std::invalid_argument("Invalid Matrix was entered\n");
            }
        }
        a._row=(unsigned int)row;
        if (a._row == 0){
            throw std::invalid_argument("Invalid Matrix was entered\n");
        }
        a._col = (unsigned int)(mat_a.size()) / a._row;
        mat_a.resize(a._row * a._col);
        Matrix ans{mat_a,(int)a._row,(int)a._col};
        a._mat = ans._mat;
        return is;
    }

}




