#include "fileamplifier.h"
#include "matio.h"
#include "QDebug"
#include "iostream"
FIleAmplifier::FIleAmplifier()
{
    this->status=false;
    this->data_status=false;
    initConnectWidget();
}

void FIleAmplifier::start()
{
    data_status=true;
}

void FIleAmplifier::stop()
{
    data_status=false;
}

QStringList FIleAmplifier::getChannelName()
{
    QString channel_label="FP1,FZ,F3,F7,FT9,FC5,FC1,C3,T7,TP9,CP5,CP1,PZ,P3,P7,O1,OZ,O2,P4,P8,TP10,CP6,CP2,CZ,C4,T8,resp,GSR,TEMP,Blood,ECG,EMG";
    QStringList label=channel_label.split(",");
    return label;
}

quint8 FIleAmplifier::getChannnelNum()
{
    return 32;
}

quint16 FIleAmplifier::getSampleRate()
{
    return 250;
//    return srate;
}

QWidget *FIleAmplifier::getConfigWidget()
{
    return  NULL;
}

QWidget *FIleAmplifier::getConnectWidget()
{
    return connectwidget;
}

QList<double> FIleAmplifier::getOneData()
{
    QList<double> data;
    return data;
}

QList<QList<double> > FIleAmplifier::getArrayData()
{
    QList<QList<double> > data;
    if(data_status)
    {
        data=eegdata.getData();
    }
    return data;
}

QList<uint8_t> FIleAmplifier::getEEGGameIndex()
{
     QList<uint8_t> data={0,1,2,3,4,5,6,7,8,9,10,11};
     return data;
}

QList<uint8_t> FIleAmplifier::getEEGIndex()
{
    QList<uint8_t> data={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    return data;
}

QList<uint8_t> FIleAmplifier::getMuscleIndex()
{
    QList<uint8_t> data={31};
    return data;
}

QList<uint8_t> FIleAmplifier::getBreathIndex()
{
    QList<uint8_t> data={26};
    return data;
}

QList<uint8_t> FIleAmplifier::getHeartIndex()
{
    QList<uint8_t> data={30};
    return data;
}

bool FIleAmplifier::connectStatus()
{
    return status;
}

void FIleAmplifier::initConnectWidget()
{
    connectwidget=new ConnectWidget;
    connect(connectwidget,&ConnectWidget::connectDevice,this,&FIleAmplifier::readData);
    connect(connectwidget,&ConnectWidget::closeDevice,this,&FIleAmplifier::closeDevice);
}

void FIleAmplifier::closeDevice()
{
    this->eegdata.clear();
    this->status=false;
    this->connectwidget->setConnectStatus("连接");
}

void FIleAmplifier::readData(QString path)
{
    mat_t *mat_file=Mat_Open(path.toStdString().c_str(),MAT_ACC_RDONLY);
    if(mat_file)
    {
        matvar_t *eeg=Mat_VarRead(mat_file,"EEG");
        matvar_t *data=Mat_VarGetStructFieldByName(eeg,"data",0);
        matvar_t *srate=Mat_VarGetStructFieldByName(eeg,"srate",0);
        matvar_t *chanlocs=Mat_VarGetStructFieldByName(eeg,"chanlocs",0);
        //数据
        eegdata.setData(data->data,data->dims[1],data->dims[0]);
        //采样率
        int *srate_value=(int*)(srate->data);
        this->srate=*srate_value;
        //通道名字
        QStringList channel_value;
        for(int i=0;i<int(chanlocs->dims[0]);i++)
        {
            matvar_t *label=Mat_VarGetStructFieldByName(chanlocs,"labels",i);
            QString label_value=QString::fromLocal8Bit((char*)label->data,int(label->dims[1]));
            channel_value.append(label_value);
        }
        this->channel_labels=channel_value;
        this->channel_num=channel_value.size();
        Mat_VarFree(eeg);
        Mat_Close(mat_file);
        this->status=true;
        this->connectwidget->setConnectStatus("断开");
    }
    else
    {
        qDebug()<<"文件打开失败";
    }
}

