#include "widget.h"
#include "ui_widget.h"
//#include "_matrix.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <QMutex>
#include <QString>


using namespace std;

extern int chosenChannelNum;
extern int* chosenChannel;
extern double** passData_test1;
extern double** passData_test2;
extern QMutex mutex_FeatureGet;
extern bool isTimeForCollectData1;
extern bool isTimeForCollectData2 ;
extern bool isEndForCollectData1 ;
extern bool isEndForCollectData2;
extern bool SSVEPTestThreadStopped ;
extern bool DataThreadStopped;


//主线程


Widget::Widget(QWidget *parent) :
    QWidget(parent),threadData_test(NULL),threadSSVEPTest(NULL),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(0,0,0);");




    
    //闪烁刺激实现：设了7个定时器控制pushButton组件的颜色定时翻转，实现特定频率的黑白闪烁刺激

    ui->pushButton_7->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_8->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_9->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton  ->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_4->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_5->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    ui->pushButton_6->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    timer1=new QTimer;
    timer2=new QTimer;
    timer3=new QTimer;
    timer4=new QTimer;
    timer5=new QTimer;
    timer6=new QTimer;
    QObject::connect(timer1,SIGNAL(timeout()),this,SLOT(Timer1timeout()));
    QObject::connect(timer2,SIGNAL(timeout()),this,SLOT(Timer2timeout()));
    QObject::connect(timer3,SIGNAL(timeout()),this,SLOT(Timer3timeout()));
    QObject::connect(timer4,SIGNAL(timeout()),this,SLOT(Timer4timeout()));
    QObject::connect(timer5,SIGNAL(timeout()),this,SLOT(Timer5timeout()));
    QObject::connect(timer6,SIGNAL(timeout()),this,SLOT(Timer6timeout()));
    num_time1=0;
    num_time2=0;
    num_time3=0;
    num_time4=0;
    num_time5=0;
    num_time6=0;
    //save data file

}

Widget::~Widget()
{
    delete ui;
    ui=NULL;
    delete timer1;
    timer1=NULL;
    delete timer2;
    timer2=NULL;
    delete timer3;
    timer3=NULL;
    delete timer4;
    timer4=NULL;
    delete timer5;
    timer5=NULL;
    delete timer6;
    timer6=NULL;

    if(chosenChannel != NULL)
    {
        delete [] chosenChannel;
        chosenChannel = NULL;
    }
    if(NULL != threadSSVEPTest)
    {
        threadSSVEPTest->wait();
        delete threadSSVEPTest;
        threadSSVEPTest = NULL;
    }

    if(NULL != threadData_test)
    {
        threadData_test->wait();
        delete threadData_test;
        threadData_test = NULL;
    }
    if(NULL != passData_test1)
    {
        for(int i = 0;i<chosenChannelNum;i++)
        {
            delete []passData_test1[i];
            passData_test1[i] = NULL;
        }
        delete []passData_test1;
        passData_test1 = NULL;
    }

    if(NULL != passData_test2)
    {
        for(int i = 0;i<chosenChannelNum;i++)
        {
            delete []passData_test2[i];
            passData_test2[i] = NULL;
        }
        delete []passData_test2;
        passData_test2 = NULL;
    }






}

//开始数据采集线程，采用双缓存

void Widget::on_pushButton_9_clicked()
{
    if(passData_test1==NULL)
    {
        channel_sel_dialog w1;
        w1.exec();
    }
    passData_test1 = new double*[chosenChannelNum];
    {
        for(int i = 0;i<chosenChannelNum;i++)
        {
            passData_test1[i] = new double[mydatalength2];
        }
    }
    qDebug()<<"passData_test after new: "<<passData_test1;
    passData_test2 = new double*[chosenChannelNum];
    {
        for(int i = 0;i<chosenChannelNum;i++)
        {
            passData_test2[i] = new double[mydatalength2];
        }
    }
    qDebug()<<"passData_test after new: "<<passData_test2;

    if(threadData_test==NULL)
    {

        threadData_test = new collectdatathread(mydatalength2,passData_test1,passData_test2);
        QObject::connect(threadData_test,SIGNAL(StopMovepTest()),this,SLOT(on_pushButton_8_clicked()));
    }
    if(threadSSVEPTest==NULL)
    {
        threadSSVEPTest = new ssveptestthread(mydatalength2,passData_test1,passData_test2);
        //QObject::connect(threadSSVEPTest,SIGNAL(logCCAVal(int)),this,SLOT(logCCAVal(int)));
    }
    DataThreadStopped = false;
    SSVEPTestThreadStopped = false;
    threadSSVEPTest->start();
    for(int i = 0;i<3000;)
    {
        i++;
    }
    threadData_test->start();
    for(int i = 0;i<3000;)
    {
        i++;
    }
}




void Widget::on_pushButton_7_clicked()
{
    //方块闪烁定时器
    timer1->start(91);//5.5Hz
    for(int j=0;j<500;)//延时，防止theadData线程运行完毕后threadMovepTrain还没运行到waitdata.wait(&waitdata_mutex);从而导致程序阻塞
    {
        j++;
    }
    timer2->start(75);//6.7Hz
    for(int j=0;j<500;)//延时，防止theadData线程运行完毕后threadMovepTrain还没运行到waitdata.wait(&waitdata_mutex);从而导致程序阻塞
    {
        j++;
    }
    timer3->start(66);//7.5Hz
    for(int j=0;j<500;)//延时，防止theadData线程运行完毕后threadMovepTrain还没运行到waitdata.wait(&waitdata_mutex);从而导致程序阻塞
    {
        j++;
    }
    timer4->start(58);//8.6Hz
    for(int j=0;j<500;)//延时，防止theadData线程运行完毕后threadMovepTrain还没运行到waitdata.wait(&waitdata_mutex);从而导致程序阻塞
    {
        j++;
    }
    timer5->start(50);//10Hz
    for(int j=0;j<500;)//延时，防止theadData线程运行完毕后threadMovepTrain还没运行到waitdata.wait(&waitdata_mutex);从而导致程序阻塞
    {
        j++;
    }
    timer6->start(42);//12Hz
    for(int j=0;j<500;)//延时，防止theadData线程运行完毕后threadMovepTrain还没运行到waitdata.wait(&waitdata_mutex);从而导致程序阻塞
    {
        j++;
    }
}
void Widget::on_pushButton_8_clicked()
{
    SSVEPTestThreadStopped = true;
    DataThreadStopped = true;
    //system("cd ..");
    system("./main_desk -qws");
    exit(0);
}
void Widget::Timer1timeout()
{

    if(num_time1%2==0)
    {
        ui->pushButton->setStyleSheet("background-color: rgb(0,0,0);border-color:rgb(0,0,0);");
    }
    else
    {
        ui->pushButton->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    }
    num_time1++;
}
void Widget::Timer2timeout()
{
    if(num_time2%2==0)
    {
        ui->pushButton_2->setStyleSheet("background-color: rgb(0,0,0);border-color:rgb(0,0,0);");
    }
    else
    {
        ui->pushButton_2->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    }
    num_time2++;
}
void Widget::Timer3timeout()
{
    if(num_time3%2==0)
    {
        ui->pushButton_3->setStyleSheet("background-color: rgb(0,0,0);border-color:rgb(0,0,0);");
    }
    else
    {
        ui->pushButton_3->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    }
    num_time3++;
}
void Widget::Timer4timeout()
{
    if(num_time4%2==0)
    {
        ui->pushButton_4->setStyleSheet("background-color: rgb(0,0,0);border-color:rgb(0,0,0);");
    }
    else
    {
        ui->pushButton_4->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    }
    num_time4++;
}
void Widget::Timer5timeout()
{
    if(num_time5%2==0)
    {
        ui->pushButton_5->setStyleSheet("background-color: rgb(0,0,0);border-color:rgb(0,0,0);");
    }
    else
    {
        ui->pushButton_5->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    }
    num_time5++;
}
void Widget::Timer6timeout()
{
    if(num_time6%2==0)
    {
        ui->pushButton_6->setStyleSheet("background-color: rgb(0,0,0);border-color:rgb(0,0,0);");
    }
    else
    {
        ui->pushButton_6->setStyleSheet("background-color: rgb(255,255,255);border-color:rgb(255,255,255);");
    }
    num_time6++;
}

