#include "widget.h"
#include "collectdatathread.h"
#include "ssveptestthread.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QDialog>
#include <QMutex>
#include <QWSServer>

#define mydatalength2  1950

volatile int chosenChannelNum =0;  //用于设置所选通道数，在数据采集线程中用到，当训练时其是在通道选择界面赋值，当测试时，就在读取测试参数函数中赋值
int* chosenChannel=NULL;    //用于设置所选通道(0,1,2,3,4,5,6,7)，当训练时其是在通道选择界面中分配内存，当测试时，就在读取测试参数函数中分配内存并赋值，两者都在数据采集线程中释放内存
double** passData_test1 = NULL; //
double** passData_test2 = NULL;
QMutex mutex_FeatureGet;    //用于特征向量的提取
bool DataThreadStopped = true; //用于控制数据采集线程的开关
bool SSVEPTestThreadStopped = true;//用于控制SSVEP测试线程的开关
bool isTimeForCollectData1 = false;//双缓存读取数据开关1
bool isTimeForCollectData2 = false;//双缓存读取数据开关2
bool isEndForCollectData1 = false;//双缓存读取数据开关1
bool isEndForCollectData2 = false;//双缓存读取数据开关2



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
