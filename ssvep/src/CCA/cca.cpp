#include "cca.h"
#include "_matrix.h"
#include "string"
#define PI acos(-1)
CCA::CCA()
{

}

int CCA::Classify(double X[][mydatalength2], int channel_num)
{
    //为数据开辟临时空间
    double **data=new double*[channel_num];
    for(int i=0;i<channel_num;i++)
    {
        data[i]=new double[mydatalength2];
    }
    double **REF=new double*[4];
    for(int i=0;i<4;i++)
    {
        REF[i]=new double[mydatalength2];
    }
    //开始CCA计算过程
    double result[REFNUM];
    for(int i=0;i<REFNUM;i++)
    {
        //复制数据
        for(int j=0;j<channel_num;j++)
        {
            memcpy(data[j],X[j],sizeof (double)*mydatalength2);
        }
        //复制参考
        for(int j=0;j<4;j++)
        {
            memcpy(REF[j],this->REF[i][j],sizeof (double)*mydatalength2);
        }
        //开始计算
        result[i]=Caculate(data,REF,channel_num,REFNUM,mydatalength2);
        if(result[i]<=0.15)
        {
            result[i]=0;
        }
    }
    //释放临时空间
    for(int i=0;i<channel_num;i++)
    {
        delete []data[i];
        data[i]=NULL;
    }
    delete []data;
    data=NULL;
    for(int i=0;i<4;i++)
    {
        delete []REF[i];
        REF[i]=NULL;
    }
    delete []REF;
    REF=NULL;
    return max(result,REFNUM);
}
/*
 * 输入参数：
 * X；EEG数据
 * Y：参考数据
 * P:通道数
 * q：参考数据
 * n：数据点数目
 */
double CCA::Caculate(double **X, double **Y, int p, int q, int n)
{

    _Matrix x(p, n, X);
    _Matrix y(q, n, Y);
    x = x.Centralization(1);
    y = y.Centralization(1);
    _Matrix Sxx(p, p);
    _Matrix Syy(q, q);
    _Matrix Sxy(p, q);
    _Matrix Syx(q, p);
    Sxx = x.Covariance(1);
    Syy = y.Covariance(1);
    Sxy = x.Covariance(y, 1);
    Syx = Sxy.TransposeMatrix();
    if (p <= q)
    {
        _Matrix R(p, p);
        R = Sxx.InverseMatrix() * Sxy * Syy.InverseMatrix() * Syx;
        return R.MaxEigenValue();
    }
    else
    {
        _Matrix R(q, q);
        R = Syy.InverseMatrix() * Syx * Sxx.InverseMatrix() * Sxy;
        return sqrt(R.MaxEigenValue());
    }
}

double CCA::max(double * result,int n)
{
    if(n==1)
    {
        return result[0];
    }
    double left_max=max(result,n/2);
    double right_max=(&result[n/2],n);
    if(left_max>right_max)
    {
        return left_max;
    }
    else
    {
        return right_max;
    }
}

void CCA::init()
{
    ref_rate[0]=5.454;
    ref_rate[1]=6.667;
    ref_rate[2]=7.5;
    ref_rate[3]=8.5714;
    ref_rate[4]=10;
    ref_rate[5]=12;
    ref_rate[6]=15;
    ref_rate[7]=16;
    for(int i=0;i<REFNUM;i++)
    {
        for(int j=0;j<mydatalength2;j++)
        {
            REF[i][0][j]=sin(ref_rate[i]*2*PI*(double)i/1000);
            REF[i][1][j]=cos(ref_rate[i]*2*PI*(double)i/1000);
            REF[i][2][j]=sin(ref_rate[i]*4*PI*(double)i/1000);
            REF[i][3][j]=cos(ref_rate[i]*4*PI*(double)i/1000);
        }
    }
}
