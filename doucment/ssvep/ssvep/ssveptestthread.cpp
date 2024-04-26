#include "ssveptestthread.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QWaitCondition>
#include <QMutex>
#include <iostream>


#include <ctime>

extern int chosenChannelNum;
extern int *chosenChannel;

extern bool isTimeForCollectData1;
extern bool isTimeForCollectData2;
extern bool isEndForCollectData1;
extern bool isEndForCollectData2;
extern bool SSVEPTestThreadStopped;

QMutex waitdata_mutex;
extern QWaitCondition waitdata;
extern QMutex mutex_FeatureGet;

//ssvep分类线程，
ssveptestthread::ssveptestthread(int dataNum,
                                 double **passData1,
                                 double **passData2,
                                 QObject *parent):
    QThread(parent),
    myDataNum(dataNum),
    //RESULT(NULL),
    Data1(passData1),
    Data2(passData2)

{



    //构建参考信号模板，每一个频率设置4种模板，1倍频sin 2倍频sin 1倍频cos 2倍频cos
    // 
    // 
    // 参考信号的数值根据最终设置的频率设置，如最终用8和9Hz
    //那么仅需构建以下模板信号：

       //参考信号一：5.454Hz
    /*
    REF1[0][i] = sin(8 * 2 * pi * (double)i / 1000.0);
    REF1[1][i] = cos(8 * 2 * pi * (double)i / 1000.0);
    REF1[2][i] = sin(16 * 2 * pi * (double)i / 1000.0);
    REF1[3][i] = cos(16 * 2 * pi * (double)i / 1000.0);

    REF2[0][i] = sin(9 * 2 * pi * (double)i / 1000.0);
    REF2[1][i] = cos(9 * 2 * pi * (double)i / 1000.0);
    REF2[2][i] = sin(18 * 2 * pi * (double)i / 1000.0);
    REF2[3][i] = cos(18 * 2 * pi * (double)i / 1000.0);
    
    
    */


    //ssvep信号的识别分类调用getTheIndexOfCCA函数
    //getTheIndexOfCCA(double DATA[channelNum][datalength])，DATA是存储数据的二维矩阵，通道*时间点
    //注释详见getTheIndexOfCCA函数





    matchedIndex = 0;
    double pi = 3.1416;
    for(int i =0;i<mydatalength2;i++)
    {
        DATA[0][i] = 0;
        DATA[1][i] = 0;
        DATA[2][i] = 0;
        DATA[3][i] = 0;
        DATA[4][i] = 0;
        DATA[5][i] = 0;
        DATA[6][i] = 0;
        DATA[7][i] = 0;
        DATA[8][i] = 0;
        DATA[9][i] = 0;
        DATA[10][i] = 0;
        DATA[11][i] = 0;
        DATA[12][i] = 0;
        DATA[13][i] = 0;
        DATA[14][i] = 0;
        DATA[15][i] = 0;

        //参考信号一：5.454Hz
        REF1[0][i] = sin( 5.454545454545455 * 2 * pi * (double)i / 1000.0);
        REF1[1][i] = cos( 5.454545454545455 * 2 * pi * (double)i / 1000.0);
        REF1[2][i] = sin(10.909090909090909 * 2 * pi * (double)i / 1000.0);
        REF1[3][i] = cos(10.909090909090909 * 2 * pi * (double)i / 1000.0);
        //参考信号二：6.667Hz
        REF2[0][i] = sin( 6.666666666666667 * 2 * pi * (double)i / 1000.0);
        REF2[1][i] = cos( 6.666666666666667 * 2 * pi * (double)i / 1000.0);
        REF2[2][i] = sin(13.333333333333333 * 2 * pi * (double)i / 1000.0);
        REF2[3][i] = cos(13.333333333333333 * 2 * pi * (double)i / 1000.0);
        //参考信号三:7.5Hz
        REF3[0][i] = sin( 7.500000000000000 * 2 * pi * (double)i / 1000.0);
        REF3[1][i] = cos( 7.500000000000000 * 2 * pi * (double)i / 1000.0);
        REF3[2][i] = sin(15.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF3[3][i] = cos(15.000000000000000 * 2 * pi * (double)i / 1000.0);
        //参考信号四:8.5714Hz
        REF4[0][i] = sin( 8.571428571428571 * 2 * pi * (double)i / 1000.0);
        REF4[1][i] = cos( 8.571428571428571 * 2 * pi * (double)i / 1000.0);
        REF4[2][i] = sin(17.142857142857142 * 2 * pi * (double)i / 1000.0);
        REF4[3][i] = cos(17.142857142857142 * 2 * pi * (double)i / 1000.0);
        //参考信号五:10Hz
        REF5[0][i] = sin(10.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF5[1][i] = cos(10.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF5[2][i] = sin(20.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF5[3][i] = cos(20.000000000000000 * 2 * pi * (double)i / 1000.0);

        //参考信号六:12Hz
        REF6[0][i] = sin(12.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF6[1][i] = cos(12.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF6[2][i] = sin(24.000000000000000 * 2 * pi * (double)i / 1000.0);
        REF6[3][i] = cos(24.000000000000000 * 2 * pi * (double)i / 1000.0);

    }
}

void ssveptestthread::run()
{
    qDebug()<<"ssveptestthread run";
    while(!SSVEPTestThreadStopped)
    {
        qDebug()<<"testthread lock";
        waitdata_mutex.lock();
        waitdata.wait(&waitdata_mutex);
        waitdata_mutex.unlock();
        if(isEndForCollectData1 && !isEndForCollectData2)
        {
            mutex_FeatureGet.lock();
            {
                for(int i =0;i<chosenChannelNum;i++)
                {
                    for(int j = 0;j<myDataNum;j++)
                    {
                        DATA[i][j] = Data1[i][j];
                    }
                }
            }
            mutex_FeatureGet.unlock();
            isEndForCollectData1 = false;
            isEndForCollectData2 = false;
        }

        if(!isEndForCollectData1 && isEndForCollectData2)
        {
            mutex_FeatureGet.lock();
            {
                for(int i =0;i<chosenChannelNum;i++)
                {
                    for(int j = 0;j<myDataNum;j++)
                    {
                        DATA[i][j] = Data2[i][j];
                    }
                }
            }
            mutex_FeatureGet.unlock();
            isEndForCollectData1 = false;
            isEndForCollectData2 = false;
        }
        //calculte CCA value;
        matchedIndex = getTheIndexOfCCA(DATA);
        qDebug()<<"CCA result is :"<<matchedIndex<<endl;
        //fprintf(RESULT,"%d ",matchedIndex);


        //emit logCCAVal(matchedIndex);

    }


}

double ssveptestthread::CCA(double **X, double **Y, int p, int q, int n)
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

double ssveptestthread::CCACaculate(double DATA[16][mydatalength2], double REF[4][mydatalength2])
{
    double** data = new double* [16];

    for (int i = 0; i < 16; i++)
    {
        data[i] = new double[mydatalength2];
    }

    for (int i = 0; i < mydatalength2; i++)
        for (int j = 0; j < 16; j++)
        {
            //注意数据的结构，main函数用下面这个，MOVEP项目用下下面那个
            //data[j][i] = DATA[j * 1950 + i];
            data[j][i] = DATA[j][i];
        }

    double** ref = new double* [4];

    for (int i = 0; i < 4; i++)
    {
        ref[i] = new double[mydatalength2];
    }

    for (int i = 0; i < mydatalength2; i++)
        for (int j = 0; j < 4; j++)
        {
            ref[j][i] = REF[j][i];
        }

    double ans = CCA(data, ref, 16, 4, mydatalength2);

    for(int mm = 0;mm<16;mm++)
    {
        delete []data[mm];
        data[mm] = NULL;
    }
    delete []data;
    data = NULL;

    for(int mm = 0;mm<4;mm++)
    {
        delete []ref[mm];
        ref[mm] = NULL;
    }
    delete []ref;
    ref = NULL;





    //delete[] data;

    //delete[] ref;

    return ans;
}






// 系统最终用到N个参考信号REF，这里就相应调用N次 CCACaculate 得到 cca1...ccaN，
//CCA计算后的阈值需要测试一下，不同的放大器和数据大小会对此阈值产生不同的影响

int ssveptestthread::getTheIndexOfCCA(double DATA[16][mydatalength2])
{
    int index = 0;
    double cca1 = CCACaculate(DATA, REF1);//5.5
  
    double cca2 = CCACaculate(DATA, REF2);//6.7
  
    double cca3 = CCACaculate(DATA, REF3);//7.5

    double cca4 = CCACaculate(DATA, REF4);//8.7

    double cca5 = CCACaculate(DATA, REF5);//10

    double cca6 = CCACaculate(DATA, REF6);//12


    //设定一个CCA计算后的阈值，小于该阈值直接赋值为0，减少噪声和自发脑电的影响
    //相应地进行修改
    if (cca1 <= 0.15)
    {
        cca1 = 0.0;
    }
    if (cca2 <= 0.15)
    {
        cca2 = 0.0;
    }
    if (cca3 <= 0.15)
    {
        cca3 = 0.0;
    }
    if (cca4 <= 0.15)
    {
        cca4 = 0.0;
    }
    if (cca5 <= 0.15)
    {
        cca5 = 0.0;
    }
    if (cca6 <= 0.15)
    {
        cca6 = 0.0;
    }

    //相应地修改
    double theMax = fmax(cca1, fmax(cca2, fmax(cca3, fmax(cca4, fmax(cca5, cca6)))));


    printf("%f\n", theMax);

    //相应地修改
    if (theMax == cca1)
    {
        index = 1;
    }
    if (theMax == cca2)
    {
        index = 2;
    }
    if (theMax == cca3)
    {
        index = 3;
    }
    if (theMax == cca4)
    {
        index = 4;
    }
    if (theMax == cca5)
    {
        index = 5;
    }
    if (theMax == cca6)
    {
        index = 6;
    }

    return index;
}

ssveptestthread::~ssveptestthread()
{

}

