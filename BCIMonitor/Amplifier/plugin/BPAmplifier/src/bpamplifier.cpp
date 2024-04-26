#include "bpamplifier.h"
#include "QDebug"
#include "QThread"
#include <QList>
#include "QTimer"
BPAmplifier::BPAmplifier()
{
    init();
}
BPAmplifier::~BPAmplifier()
{
    QThread::msleep(10);
    deleteConfigWidget();
    deleteConnectWidget();
    deleteRdh();
    deleteConnecteThread();
}
void BPAmplifier::start()
{
    amplifier.StartAcquisition(RM_NORMAL);
}
void BPAmplifier::stop()
{
    amplifier.StopAcquisition();
}
QStringList BPAmplifier::getChannelName()
{
//     QString channel_label="Fp1,Fp2,F3,F4,C3,C4,P3,P4,O1,O2,F7,F8,T7,T8,P7,P8,Fz,Cz,Pz,IO,FC1,FC2,CP1,CP2,FC5,FC6,CP5,CP6,FT9,FT10,TP9,TP10";
     QString channel_label="FP1,FZ,F3,F7,FT9,FC5,FC1,C3,T7,TP9,CP5,CP1,PZ,P3,P7,O1,OZ,O2,P4,P8,TP10,CP6,CP2,CZ,C4,T8,resp,GSR,TEMP,Blood,ECG,EMG";
     QStringList label=channel_label.split(",");
     return label;
}

quint8 BPAmplifier::getChannnelNum()
{
    return 32;
}

quint16 BPAmplifier::getSampleRate()
{
    return 250;
}
QWidget *BPAmplifier::getConfigWidget()
{
    return configWidget;
}
QWidget *BPAmplifier::getConnectWidget()
{
    return connectWidget;
}
QList<double> BPAmplifier::getOneData()
{
    QList<double> data;
    return data;
}
QList<QList<double> > BPAmplifier::getArrayData()
{
    QList<QList<double>> data;
    std::vector<std::vector<float>> vvfData;
    //采集器的数据获取
    int nSamples = rdh->ParseRawData(amplifier, vvfData);
    if(nSamples!=0)
    {
        for(int i=0;i<nSamples;++i){
            //数据截断只取32通道数据
            std::vector<double> eeg = std::vector<double>(vvfData[i].begin(), vvfData[i].begin()+26);
            std::vector<double> other=std::vector<double>(vvfData[i].begin()+32,vvfData[i].begin()+32+6);
            QList<double> temp;
            temp.append(QVector<double>::fromStdVector(eeg).toList());
            temp.append(QVector<double>::fromStdVector(other).toList());
            data.append(temp);
        }
    }
    return data;
}

bool BPAmplifier::connectStatus()
{
    return status;
//    int status;
//    amplifier.GetProperty(status,DPROP_I32_ConnectionState);
//    if(status==2)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
}
// EEG游戏通道索引，12个
QList<uint8_t> BPAmplifier::getEEGGameIndex()
{
    return {0,1,2,3,4,5,6,7,8,9,10,11};
}

// EEG全部通道索引
QList<uint8_t> BPAmplifier::getEEGIndex()
{
    return {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
}

QList<uint8_t> BPAmplifier::getBreathIndex()
{
    return {26};
}

QList<uint8_t> BPAmplifier::getMuscleIndex()
{
    return {31};
}

QList<uint8_t> BPAmplifier::getHeartIndex()
{
    return {30};
}


void BPAmplifier::init()
{
    this->family=0;
    this->type=0;
    rdh=NULL;
    configWidget=NULL;
    initConnectThread();
    initConnectWidget();
    initCheckTask();


}
void BPAmplifier::initRdh()
{
    rdh=new RawDataHandler(amplifier);
}

void BPAmplifier::deleteRdh()
{
    if(rdh!=NULL)
    {
        delete rdh;
    }
}

void BPAmplifier::deleteConfigWidget()
{
    if(configWidget!=NULL)
    {
        delete configWidget;
    }
}

void BPAmplifier::initCheckTask()
{
    connect_check_task=new QTimer;
    connect(connect_check_task,&QTimer::timeout,this,[=](){
        emit statusSignal();
    });
    connect_check_task->start(1000);
}

void BPAmplifier::deleteConnectWidget()
{
    if(connectWidget!=NULL)
    {
        delete connectWidget;
    }
}
void BPAmplifier::initConnectWidget()
{
    //连接窗口初始化
    connectWidget=new ConnectDialog;
    connectWidget->setFamily({"LiveAmp","actiCHamp"});
    connectWidget->setType({"any","usb","bluetooth","sim"});
    //信号初始化
    connect(connectWidget,&ConnectDialog::familyChanged,this,&BPAmplifier::setDeviceFamily);
    connect(connectWidget,&ConnectDialog::typeChanged,this,&BPAmplifier::setInterFaceType);
    connect(connectWidget,&ConnectDialog::search,this,&BPAmplifier::SearchDeviceNum);
    connect(connectWidget,&ConnectDialog::connect,this,&BPAmplifier::ConnectDevice);

}

void BPAmplifier::reviceSearchResult(int num)
{
    connectWidget->setDeviceNum(num);
}

void BPAmplifier::receiveConnectResult(bool result)
{
    if(result)
    {
        initRdh();
        connectWidget->setStatus(true);
        connectWidget->showError("设备连接成功");

    }
    else
    {
        connectWidget->showError("设备连接失败");
    }
}

void BPAmplifier::receviceStatus(bool)
{


}

void BPAmplifier::setDeviceFamily(int family)
{
    this->family=family;
}

void BPAmplifier::setInterFaceType(int type)
{
    this->type=type;
}
void BPAmplifier::SearchDeviceNum()
{
   emit searchSignal(this->family,this->type);
}

void BPAmplifier::ConnectDevice(int DeviceId)
{
    int status;
    int res=amplifier.GetProperty(status,DPROP_I32_ConnectionState);
    if(status!=2)
    {
        emit connectSignal(DeviceId);
    }
    else
    {
        amplifier.Close();
        amplifier.m_hAmplifier=NULL;
        this->connectWidget->setStatus(false);

    }

}

void BPAmplifier::initConnectThread()
{
    connect_task=new ConnectTask;
    connect_thread=new QThread;
    connect_task->moveToThread(connect_thread);

    connect_task->setAmplifier(&amplifier);
    //设备搜索
    connect(connect_task,&ConnectTask::searchFinished,this,&BPAmplifier::reviceSearchResult,Qt::QueuedConnection);
    connect(this,&BPAmplifier::searchSignal,connect_task,&ConnectTask::SearchDeviceNum);
    //设备连接
    connect(connect_task,&ConnectTask::connectResult,this,&BPAmplifier::receiveConnectResult,Qt::QueuedConnection);
    connect(this,&BPAmplifier::connectSignal,connect_task,&ConnectTask::connectDevice);

    connect(this,&BPAmplifier::statusSignal,connect_task,&ConnectTask::connectStatus);
    connect(connect_task,&ConnectTask::status,this,[=](bool status){
        this->status=status;
    });
    //开启线程
    connect_thread->start();
}

void BPAmplifier::deleteConnecteThread()
{
    connect_thread->quit();
    QThread::sleep(1);
    delete connect_task;
    delete connect_thread;
}

