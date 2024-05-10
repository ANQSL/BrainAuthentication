#include "cca.h"
#include "_matrix.h"
#include "string"
#include "QDebug"
#include "QFile"
#include "QDateTime"
#define PI acos(-1)
CCA::CCA()
{

}

void CCA::start(quint8 mark)
{
      this->mark=mark;
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

void CCA::append(QList<double> data)
{
    for(int i=0;i<data.size();i++)
    {
        data[i]=filter.iir(i,data[i]);
    }
    if(mark)
    {
        for(int i=0;i<32;i++)
        {
            this->data[i][current_data_num]=data[i];
        }
        current_data_num++;
        if(current_data_num==mydatalength2)
        {
            int result=Classify(this->data,32);
            qDebug()<<result;
            current_data_num=0;
            all_num++;
            if(result==mark)
            {
                valid_num++;
            }
            ssvepSave();
            mark=0;

        }
    }
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

void CCA::ssvepSave()
{
    QString path=QDateTime::currentDateTime().toString("yyyy_MM_dd")+"_"+QString::number(mark)+"_ssvep.bin";
//    qDebug()<<path;
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    for(int i=0;i<32;i++)
    {
        file.write((char*)data[i],mydatalength2*8);
    }
    file.close();
}

void CCA::init()
{
    //参数初始化
    current_data_num=0;
    mark=0;
    all_num=0;
    valid_num=0;
    filter.init(32,1000,1,15);

    //参考识别
    ref_rate[0]=8;
    ref_rate[1]=8.6;
    ref_rate[2]=9;
    ref_rate[3]=9.6;
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
