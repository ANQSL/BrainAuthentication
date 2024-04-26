#include "collectdatathread.h"
#include <QMessageBox>
#include <sys/wait.h>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
//#include "config.h"
#include <iostream>
#include <fstream>

#ifndef _CTL_H_
#define _CTL_H_
#define CTL_MAGIC 'k'
#define reset  _IOR(CTL_MAGIC, 0, unsigned long)
#define rempty  _IOR(CTL_MAGIC, 1, unsigned long)
#define rfull  _IOR(CTL_MAGIC, 2, unsigned long)
#endif

//采集数据线程，双缓存从嵌入式设备中读取数据

QWaitCondition waitdata;
extern bool isTimeForCollectData1;
extern bool isTimeForCollectData2;
extern bool isEndForCollectData1;
extern bool isEndForCollectData2;
extern bool SSVEPTestThreadStopped;
extern bool DataThreadStopped;  //用于控制数据采集线程的开关

extern int chosenChannelNum;  //用于设置所选通道数，在数据采集线程中用到，当训练时其是在通道选择界面赋值，当测试时，就在读取测试参数函数中赋值
extern int *chosenChannel;  //用于设置所选通道(0,1,2,3,4,5,6,7)，当训练时其是在通道选择界面中分配内存，当测试时，就在读取测试参数函数中分配内存并赋值，两者都在数据采集线程中释放内存

extern QMutex mutex_FeatureGet; //用于特征向量的提取



collectdatathread::collectdatathread(int fixedSizedNum,double** passData1,double** passData2,QObject *parent) :
    QThread(parent)
{
    AD_buffer = new char[48];   //每次从AD中读48字节，每通道3字节、1采样点
    EEGuse1 = new double*[chosenChannelNum];
    EEGuse2 = new double*[chosenChannelNum];
    //EEGuse[][]的空间分配必须和widget.cpp中passData_test[][]或passData_train[][]的分配一致
    {
        for(int i = 0;i<chosenChannelNum;i++)
        {
            //qDebug()<<"EEGuse[][] "<<fixedSizedNum<<" points";
            EEGuse1[i] = new double[fixedSizedNum];
            EEGuse2[i] = new double[fixedSizedNum];
        }
        eigenvectorNum = fixedSizedNum;
    }
    for(int i = 0;i<16;i++)
        gm_pBuffer[i] = 0.0;

    Y1 = passData1;
    Y2 = passData2;

    sepFlag = 0;
    isTimeForCollectData1 = true;
    isTimeForCollectData2 = false;
    isEndForCollectData1 = false;
    isEndForCollectData2 = false;
    EEG_file = new FILE*[16];
        EEG_file[0] = fopen("EEG_1.txt","w+");
        if(EEG_file[0]==NULL)
        {
            qDebug()<<"creat EEG_1.txt failed!\n";
            exit(1);
        }
        EEG_file[1] = fopen("EEG_2.txt","w+");
        EEG_file[2] = fopen("EEG_3.txt","w+");
        EEG_file[3] = fopen("EEG_4.txt","w+");
        EEG_file[4] = fopen("EEG_5.txt","w+");
        EEG_file[5] = fopen("EEG_6.txt","w+");
        EEG_file[6] = fopen("EEG_7.txt","w+");
        EEG_file[7] = fopen("EEG_8.txt","w+");
        EEG_file[8] = fopen("EEG_9.txt","w+");
        EEG_file[9] = fopen("EEG_10.txt","w+");
        EEG_file[10] = fopen("EEG_11.txt","w+");
        EEG_file[11] = fopen("EEG_12.txt","w+");
        EEG_file[12] = fopen("EEG_13.txt","w+");
        EEG_file[13] = fopen("EEG_14.txt","w+");
        EEG_file[14] = fopen("EEG_15.txt","w+");
        EEG_file[15] = fopen("EEG_16.txt","w+");





}

//线程运行 重载run函数
void collectdatathread::run()
{
    int AD_fd;
    char full;
    char empty;
    int i_error = 0;
    //加载字符驱动设备ADS1278
    AD_fd = open("/dev/ADS1278",O_RDWR);
    if(AD_fd<0)
    {
        QMessageBox::information(NULL,"warning","Can't open the ADS1278 device,collect data thread will close!");
        emit StopMovepTest();
        DataThreadStopped = true;
    }
    full = ioctl(AD_fd,rfull,0);
    qDebug()<<"full is: "<<full;
    empty = ioctl(AD_fd,rempty,0);
    qDebug()<<"empty is: "<<empty;
    ioctl(AD_fd,reset,0);
    full = ioctl(AD_fd,rfull,0);
    qDebug()<<"full is: "<<full;
    empty = ioctl(AD_fd,rfull,0);
    qDebug()<<"empty is: "<<empty;
    qDebug()<<"open ADS1278 device success!\n";
    //当DataThreadStopped =false，开始读取AD_buffer中的数据
    while (!DataThreadStopped)
    {
        if(read(AD_fd,AD_buffer,48) != -1)
        {
            unsigned int t;
            for(int m = 0;m < 48;m +=3)
            {
                t = (unsigned char)AD_buffer[m];
                t = t<<16;
                t = t | ((unsigned char)AD_buffer[m+1]<<8);
                t = t | ((unsigned char)AD_buffer[m+2]);
                gm_pBuffer[m/3] = (((double)((int)(t-8388608)))*0.298);
                //2500000/8388608 = 0.298
            }
            //detect 1950 points;
             //PrepareData();
            if(isTimeForCollectData1)
            {
                for(int i = 0;i<chosenChannelNum;i++)//EEG[][]数组不间断从gm_pBuffer中读取数据，与是否刺激无关
                {
                    EEGuse1[i][sepFlag] = gm_pBuffer[chosenChannel[i]];
                    fprintf(EEG_file[i],"%f ",gm_pBuffer[chosenChannel[i]]);
                }
                sepFlag += 1;
                if(sepFlag==eigenvectorNum)
                {
                    isTimeForCollectData1 = false;
                    isTimeForCollectData2 = true;
                    isEndForCollectData1 = true;
                    isEndForCollectData2 = false;
                    sepFlag = 0;

                qDebug()<<"isTimeForCollectData1!\n";
                mutex_FeatureGet.lock();
                {

                    for(int i = 0;i<chosenChannelNum;i++)
                    {
                        for(int j = 0;j<eigenvectorNum;j++)//此时的sepFlag处代表最旧的数据
                        {
                            Y1[i][j] = EEGuse1[i][j];
                        }
                    }
                }
                mutex_FeatureGet.unlock();
                waitdata.wakeAll();
                }
            }


            if(isTimeForCollectData2)
            {
                for(int i=0;i<chosenChannelNum;i++)
                {
                    EEGuse2[i][sepFlag] = gm_pBuffer[chosenChannel[i]];
                    fprintf(EEG_file[i],"%f ",gm_pBuffer[chosenChannel[i]]);
                }
                sepFlag+=1;
                if(sepFlag==eigenvectorNum)
                {
                    isTimeForCollectData1 = true;
                    isTimeForCollectData2 = false;
                    isEndForCollectData1 = false;
                    isEndForCollectData2 = true;
                    sepFlag = 0;

                    qDebug()<<"isTimeForCollectData2!\n";
                    mutex_FeatureGet.lock();
                    {

                        for(int i = 0;i<chosenChannelNum;i++)
                        {
                            for(int j = 0;j<eigenvectorNum;j++)//此时的sepFlag处代表最旧的数据
                            {
                                Y2[i][j] = EEGuse2[i][j];
                            }
                        }
                    }
                    mutex_FeatureGet.unlock();
                    waitdata.wakeAll();
                }
            }
        }
        else
        {
            i_error++;
            if(i_error>10)
            {
                DataThreadStopped = true;
            }
        }
    }
    SSVEPTestThreadStopped = true;
    DataThreadStopped = true;
    waitdata.wakeAll();
    close(AD_fd);
}

collectdatathread::~collectdatathread()
{
    if(chosenChannel != NULL)
    {
        delete [] chosenChannel;
        chosenChannel = NULL;
    }
    delete [] AD_buffer;
    AD_buffer = NULL;
    for(int i = 0;i<chosenChannelNum;i++)
    {
        delete [] EEGuse1[i];
        EEGuse1[i] = NULL;
    }
    delete [] EEGuse1;
    EEGuse1 = NULL;

    for(int i = 0;i<chosenChannelNum;i++)
    {
        delete [] EEGuse2[i];
        EEGuse2[i] = NULL;
    }
    delete [] EEGuse2;
    EEGuse2 = NULL;
}
