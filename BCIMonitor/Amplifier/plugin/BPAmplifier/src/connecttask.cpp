#include "connecttask.h"
#include "QDebug"
ConnectTask::ConnectTask(QObject *parent) : QObject(parent)
{

}
void ConnectTask::setAmplifier(CAmplifier *amplifier)
{
    this->amplifier=amplifier;
}

void ConnectTask::SearchDeviceNum(int family, int type)
{
    SetAmplifierFamily((AmplifierFamily)family);
    std::string sHWDeviceAddress ="";
    char hwi[20];
    switch (type)
    {
    case 3:
        strcpy_s(hwi, "SIM");
        break;
    case 2:
        strcpy_s(hwi, "BT");
        break;
    case 1:
        strcpy_s(hwi, "USB");
        break;
    default:
        strcpy_s(hwi, "ANY");
        break;
    }
    int num= EnumerateDevices(hwi, sizeof(hwi), (const char*)sHWDeviceAddress.data(), 0);
    emit searchFinished(num);
}

void ConnectTask::connectDevice(int DeviceId)
{
//    qDebug()<<QThread::currentThreadId();
    int res=amplifier->Open(DeviceId);
     qDebug()<<res;
    if(res==AMP_OK)
    {
        emit connectResult(true);
    }
    else {
        emit connectResult(false);
    };
}

void ConnectTask::connectStatus()
{
        int value;
        amplifier->GetProperty(value,DPROP_I32_ConnectionState);
        if(value==2)
        {
            emit status(true) ;
        }
        else
        {
            emit status(false);
        }
}
