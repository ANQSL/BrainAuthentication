#include "_matrix.h"

double  _Matrix::MaxValue(double *v, int num)
{
    double max;
    if(num==1)
        return v[0];
    else
    {
        for(int i=0;i<num-1;i++)
            max = (v[i] > v[i + 1] ? v[i] : v[i + 1]);
    }
    return max;
}

_Matrix::_Matrix(int rs, int cs)
{
    rowsize = rs;
    colsize = cs;
    arr = new double* [rs];
    for (int i = 0; i < rs; i++)
    {
        arr[i] = new double[cs];
        for (int j = 0; j < colsize; j++)
            arr[i][j] = 0;
    }
}

_Matrix::_Matrix(int a)  //构造单位正函数
{
    rowsize = a;
    colsize = a;
    arr = new double* [a];
    for (int i = 0; i < a; i++)
    {
        arr[i] = new double[a];
        for (int j = 0; j < a; j++)
        {
            if (j != i)
                arr[i][j] = 0;
            else
                arr[i][j] = 1;
        }
    }
}


_Matrix::_Matrix(_Matrix& w)
{
    rowsize = w.getRow();
    colsize = w.getCol();
    arr = new double* [rowsize];
    for (int i = 0; i < rowsize; i++)
    {
        arr[i] = new double[colsize];
        for (int j = 0; j < colsize; j++)
            arr[i][j] = w.getValue(i, j);
    }
}

_Matrix::_Matrix(int rs, int cs, double** a)  //构造函数
{
    int i, j;
    rowsize = rs;
    colsize = cs;
    arr = new double* [rs];
    for (i = 0; i < rs; i++)
        arr[i] = new double[cs];
    for (i = 0; i < rs; i++)
        for (j = 0; j < cs; j++)
        {
            arr[i][j] = a[i][j];
        }
}


double _Matrix::getValue(int row, int col)  const
{
    return arr[row][col];
}

void _Matrix::putValue(double a, int row, int col)
{
    arr[row][col] = a;
}

int _Matrix::getRow()   const
{
    return rowsize;
}

int _Matrix::getCol()   const
{
    return colsize;
}

_Matrix _Matrix::operator=(const _Matrix& w)
{
    if ((rowsize != w.getRow()) || (colsize != w.getCol()))
    {
        //	cout<<"矩阵不一致，无法传值"<<endl;
       //  ShowMessage("矩阵不一致，无法传值");
        return (*this);
    }
    for (int i = 0; i < rowsize; i++)
        for (int j = 0; j < colsize; j++)
            arr[i][j] = w.getValue(i, j);
    return (*this);
}

_Matrix  _Matrix::operator+(const _Matrix& w)
{
    _Matrix a(this->rowsize, this->colsize);
    if ((this->rowsize != w.getRow()) || (this->colsize != w.getCol()))
    {
        //cout<<"加法矩阵不一致"<<endl;
//                ShowMessage("加法矩阵不一致");
        return a;
    }
    for (int i = 0; i < this->rowsize; i++)
        for (int j = 0; j < this->colsize; j++)
            a.putValue(this->arr[i][j] + w.getValue(i, j), i, j);
    return a;
}

void _Matrix::operator+=(const _Matrix& w)
{
    //		_Matrix* a= new _Matrix(this->rowsize, this->colsize);
    if ((this->rowsize != w.getRow()) || (this->colsize != w.getCol()))
    {
        //                ShowMessage("加法矩阵不一致");
        return;
    }
    for (int i = 0; i < this->rowsize; i++)
        for (int j = 0; j < this->colsize; j++)
            this->arr[i][j] = this->arr[i][j] + w.getValue(i, j);
}

_Matrix  _Matrix::operator-(const _Matrix& w)
{
    _Matrix a(this->rowsize, this->colsize);
    if ((this->rowsize != w.getRow()) || (this->colsize != w.getCol()))
    {
        //		ShowMessage("减法矩阵不一致");
        return a;
    }
    for (int i = 0; i < this->rowsize; i++)
        for (int j = 0; j < this->colsize; j++)
            a.putValue(this->arr[i][j] - w.getValue(i, j), i, j);
    return a;
}

_Matrix _Matrix::operator*(const _Matrix& w)
{
    _Matrix m(this->rowsize, w.getCol());
    double a;

    if (this->colsize != w.getRow())
    {
        //		ShowMessage("矩阵无法相乘");
        return m;
    }

    for (int i = 0; i < this->rowsize; i++)
        for (int k = 0; k < w.getCol(); k++)
        {
            a = 0;
            for (int j = 0; j < this->colsize; j++)
                a = a + this->arr[i][j] * w.arr[j][k];
            //				m.arr[i][k]=a;
            m.putValue(a, i, k);
        }

    return m;
}

_Matrix _Matrix::operator*(const double a)
{
    _Matrix m(this->rowsize, this->colsize);

    for (int i = 0; i < this->rowsize; i++)
        for (int j = 0; j < this->colsize; j++)
        {
            m.arr[i][j] = arr[i][j] * a;
            //	m.putValue(a, i, k);
        }

    return m;
}

_Matrix _Matrix::TransposeMatrix()
{
    _Matrix transposeMatrix(colsize, rowsize);
    for (int i = 0; i < rowsize; i++)
        for (int j = 0; j < colsize; j++)
        {
            transposeMatrix.putValue(arr[i][j], j, i);
        }
    return transposeMatrix;
}

double _Matrix::MaxEigenValue()//雅库比迭代法
{
    if (this->rowsize != this->colsize)
    {
        ////		ShowMessage("不是4阶矩阵");
                //printf("不是方正");
        return 0;
    }

    int i;
    int n = this->rowsize;

    double* v = new double[n];
    double* x = new double[n];

    for (i = 0; i < n; i++)
    {
        v[i] = 0;
        x[i] = 1;
    }

    double e = 1e-5;
    double delta = 1;
    double eigenvalue1 = 0;
    double eigenvalue2 = 1;

    while (delta >= e)
    {
        eigenvalue1 = eigenvalue2;
        for (i = 0; i < n; i++)
        {
            v[i] = 0;
            for (int j = 0; j < n; j++)
                v[i] += arr[i][j] * x[j];
        }
        eigenvalue2 = MaxValue(v, n);
        for (i = 0; i < n; i++)
            x[i] = v[i] / eigenvalue2;

        delta = fabs(eigenvalue2 - eigenvalue1);
    }

    return eigenvalue2;
}

_Matrix _Matrix::InverseMatrix()
{
    _Matrix inverseMatrix(rowsize, colsize);

    if (rowsize != colsize)
    {
        //printf("非单位矩阵");
        return inverseMatrix;
    }

    for (int i = 0; i < rowsize; i++)
        for (int j = 0; j < colsize; j++)
        {
            inverseMatrix.arr[i][j] = arr[i][j];
        }


    double d, p;
    int i, j, n, * is, * js, k;
    n = rowsize;
    is = new int[n];
    js = new int[n];
    for (k = 0; k <= n - 1; k++)
    {
        d = 0.000;
        for (i = k; i <= n - 1; i++)
        {
            for (j = k; j <= n - 1; j++)
            {
                p = fabs(inverseMatrix.arr[i][j]);
                if (p > d)
                {
                    d = p;
                    is[k] = i;
                    js[k] = j;
                }
            }
        }
        if (1.0 == d + 1.0)
        {
            delete[]is;
            delete[]js;
            //printf ("矩阵求逆出错!");
            return inverseMatrix;
        }
        if (is[k] != k)
        { /*行交换*/
            for (j = 0; j <= n - 1; j++)
            {
                p = inverseMatrix.arr[k][j];
                inverseMatrix.arr[k][j] = inverseMatrix.arr[is[k]][j];
                inverseMatrix.arr[is[k]][j] = p;
            }
        }
        if (js[k] != k)
        { /*列交换*/
            for (i = 0; i <= n - 1; i++)
            {
                p = inverseMatrix.arr[i][k];
                inverseMatrix.arr[i][k] = inverseMatrix.arr[i][js[k]];
                inverseMatrix.arr[i][js[k]] = p;
            }
        }

        inverseMatrix.arr[k][k] = 1 / inverseMatrix.arr[k][k];

        for (j = 0; j <= n - 1; j++)
        {
            if (j != k)
            {
                inverseMatrix.arr[k][j] = inverseMatrix.arr[k][j] * inverseMatrix.arr[k][k];
            }
        }
        for (i = 0; i <= n - 1; i++)
        {
            if (i != k)
            {
                for (j = 0; j <= n - 1; j++)
                {
                    if (j != k)
                    {
                        inverseMatrix.arr[i][j] = inverseMatrix.arr[i][j] - inverseMatrix.arr[i][k] * inverseMatrix.arr[k][j];
                    }
                }
            }
        }
        for (i = 0; i <= n - 1; i++)
        {
            if (i != k)
            {
                inverseMatrix.arr[i][k] = -inverseMatrix.arr[i][k] * inverseMatrix.arr[k][k];
            }
        }
    }

    for (k = n - 1; k >= 0; k--)
    {
        if (js[k] != k)
        {
            for (j = 0; j <= n - 1; j++)
            {
                p = inverseMatrix.arr[k][j];
                inverseMatrix.arr[k][j] = inverseMatrix.arr[js[k]][j];
                inverseMatrix.arr[js[k]][j] = p;
            }
        }
        if (is[k] != k)
        {
            for (i = 0; i <= n - 1; i++)
            {
                p = inverseMatrix.arr[i][k];
                inverseMatrix.arr[i][k] = inverseMatrix.arr[i][is[k]];
                inverseMatrix.arr[i][is[k]] = p;
            }
        }
    }

    return inverseMatrix;
}

_Matrix _Matrix::Centralization(int flag)
{
    _Matrix m(rowsize, colsize);
    if (flag == 1)
    {
        double* a = new double[this->rowsize];
        for (int i = 0; i < rowsize; i++)
        {
            a[i] = 0.0;
            for (int j = 0; j < colsize; j++)
            {
                a[i] += arr[i][j];
            }
            a[i] = a[i] / colsize;
        }

        for (int i = 0; i < rowsize; i++)
        {
            for (int j = 0; j < colsize; j++)
            {
                m.arr[i][j] = arr[i][j] - a[i];
            }
        }
        delete[] a;
        return m;
    }
    if (flag == 2)
    {
        double* a = new double[this->colsize];
        for (int i = 0; i < colsize; i++)
        {
            for (int j = 0; j < rowsize; j++)
            {
                a[i] += arr[j][i];
            }
            a[i] = a[i] / rowsize;
        }

        for (int i = 0; i < rowsize; i++)
        {
            for (int j = 0; j < colsize; j++)
            {
                m.arr[i][j] = arr[i][j] - a[j];
            }
        }
        delete[] a;
        return m;
    }
    else
    {
        printf("参数无法识别");////其他参数不识别
    }
    return m;
}
_Matrix _Matrix::Covariance(int flag)
{
    if (flag == 1)
    {
        _Matrix SxxT(rowsize, rowsize);

        SxxT = (*this) * (this->TransposeMatrix()) * (1.0 / colsize);
        return SxxT;
    }
        if (flag == 2)
        {
            _Matrix SxTx(colsize, colsize);
            SxTx = (this->TransposeMatrix()) * (*this) * (1.0 / rowsize);
            return SxTx;
        }

    _Matrix nullMatrix(0, 0);
    return nullMatrix;
}



_Matrix _Matrix::Covariance(_Matrix y_Matrix, int flag)
{
    if (flag == 1)
    {
        if (colsize != y_Matrix.colsize)

            printf("无法求协方差矩阵");
        else
        {
            _Matrix SxyT(rowsize, y_Matrix.rowsize);
            SxyT = (*this) * (y_Matrix.TransposeMatrix()) * (1.0 / colsize);
            return SxyT;
        }
    }
    if (flag == 2)
    {
        if (rowsize != y_Matrix.rowsize)
            printf("无法求协方差矩阵");
        else
        {
            _Matrix SxTy(colsize, y_Matrix.colsize);
            SxTy = (this->TransposeMatrix()) * y_Matrix * (1.0 / rowsize);
            return SxTy;
        }
    }
    else
    {
        printf("参数无法识别");
    }
    _Matrix nullMatrix(0, 0);
    return nullMatrix;
}

_Matrix::~_Matrix()
{
    for(int i=0;i<rowsize;i++)
    {
        delete[] arr[i];
    }
    delete[]arr;
}

