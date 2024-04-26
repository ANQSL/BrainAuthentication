#ifndef COLLECTDATATHREAD_H
#define COLLECTDATATHREAD_H

#include <QThread>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <QMessageBox>
#include<sys/select.h>
#include<sys/time.h>




class collectdatathread : public QThread
{
    Q_OBJECT
public:
    explicit collectdatathread(int fixedSizedNum,double** passData1,double** passData2,QObject *parent = 0);

    ~collectdatathread();
    void PrepareData();

protected:
    void run();

private:
    char* AD_buffer;    //用于保存AD中读取的字节数
    double gm_pBuffer[16]; //用于保存拼接后的数据
    double **EEGuse1;    //用于保存所选通道的数据，从gm_pBuffer中读数据
    double **EEGuse2;    //用于保存所选通道的数据，从gm_pBuffer中读数据
    double **Y1;        //用于接收passData1的指针
    double **Y2;        //用于接收passData1的指针
    int sepFlag;    //用于指示从gm_pBuffer向EEGuse读取数据的位置
    int eigenvectorNum; //提取的特征向量的长度
    FILE **EEG_file;

//    FILE **EEG;


signals:
    void StopMovepTest();

public slots:

};

#endif // COLLECTDATATHREAD_H
