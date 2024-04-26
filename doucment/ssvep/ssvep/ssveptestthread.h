#ifndef SSVEPTESTTHREAD_H
#define SSVEPTESTTHREAD_H

#include <QThread>
#include "_matrix.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <fstream>
#include <QTextEdit>

extern bool isTimeForCollectData1;
extern bool isTimeForCollectData2;
extern bool isEndForCollectData1;
extern bool isEndForCollectData2;
extern bool SSVEPTestThreadStopped;




using namespace std;

class ssveptestthread : public QThread

{
    Q_OBJECT
public:
    explicit ssveptestthread(int dataNum,
                             double **passData1,
                             double **passData2,
                             QObject *parent =0);
    ~ssveptestthread();
    int getTheIndexOfCCA(double DATA[16][mydatalength2]);
    void run();
    int matchedIndex;
    //QTextEdit *textEdit;
      //FILE *RESULT;


private:
    int myDataNum;
    double **Data1;
    double **Data2;
    //存放脑电数据
    double DATA[16][mydatalength2];
    //参考信号一
    double REF1[4][mydatalength2];
    //参考信号二
    double REF2[4][mydatalength2];
    //参考信号三
    double REF3[4][mydatalength2] ;
    //参考信号四
    double REF4[4][mydatalength2] ;
    //参考信号五
    double REF5[4][mydatalength2];
    //参考信号六
    double REF6[4][mydatalength2] ;
    //参考信号七
    double REF7[4][mydatalength2] ;
    //参考信号八
    double REF8[4][mydatalength2] ;

    double CCA(double** X, double** Y, int p, int q, int n);
    double CCACaculate(double DATA[16][mydatalength2], double REF[4][mydatalength2]);



signals:
    void movetarget();
   // void logCCAVal(int val);
public slots:

};

#endif // SSVEPTESTTHREAD_H
