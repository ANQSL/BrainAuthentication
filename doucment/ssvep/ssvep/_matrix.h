#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define mydatalength2 1950

class _Matrix
{
private:
    double**    arr;
    int rowsize;
    int colsize;
    double  MaxValue(double* v, int num);
public:
    _Matrix(int rs, int cs);  //构造函数
    _Matrix(int a);  //构造单位正函数
    _Matrix(_Matrix& w);
    _Matrix(int rs, int cs, double** a);  //构造函数
    ~_Matrix(void);   //析构函数
    double getValue(int row, int col) const;
    void putValue(double a, int row, int col);
    int getRow() const;
    int getCol() const;
    _Matrix operator=(const _Matrix& w);
    _Matrix  operator+(const _Matrix& w);
    void operator+=(const _Matrix& w);
    _Matrix  operator-(const _Matrix& w);
    _Matrix operator*(const _Matrix& w);
    _Matrix operator*(const double a);
    _Matrix TransposeMatrix();
    double MaxEigenValue();//雅库比迭代法求特征值
    _Matrix InverseMatrix();//矩阵求逆——全选主元高斯-约当(Gauss-Jordan)法
    _Matrix Centralization(int flag);//中心化
    _Matrix Covariance(int flag);//自相关
    _Matrix Covariance(_Matrix y_Matrix, int flag);//互相关
};








#endif // _MATRIX_H
