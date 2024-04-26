#include "amplifer.h"
#include "dataanalysis.h"
#include "encode.h"
#include "eegdata.h"
#include "connectwidget.h"
#include "QDebug"
Amplifer::Amplifer()
{
    init();
    setConnect();
}

Amplifer::~Amplifer()
{
    if(serial_data->isOpen())
    {
       stop();
    }
    delete serial_data;
    delete eegdata;
    delete encode;
    delete analysis;
    delete connectwidget;
}
void Amplifer::setPort(QString name)
{
    serial_data->setPortName(name);
    device_param.serial_name=name;
}

bool Amplifer::setBaudRate(quint32 band_rate)
{
    bool isok=serial_data->setBaudRate(band_rate);
    if(isok)
    {
        device_param.baud_rate=band_rate;
        return true;
    }
    else
    {
        return false;
    }
}

void Amplifer::start()
{
    QByteArray buffer=encode->start();
    serial_data->write(buffer);
}

void Amplifer::stop()
{
    QByteArray buffer=encode->stop();
    serial_data->write(buffer);
}

void Amplifer::setEEGSampleRate(int rate)
{
    QByteArray buffer=encode->EEGSampleRate(rate);
    serial_data->write(buffer);
}

QList<QList<double>> Amplifer::getData()
{
    QList<QList<double>> data=eegdata->getData();
    return data;
}

QWidget *Amplifer::getConnectWidget()
{
    return connectwidget;
}

QStringList Amplifer::getChannelName()
{
    return {"FP2","F4","F8","C4",
        "T4","P4","T6","O2",
        "FP1","F7","F3","T3",
        "C3","T5","P3","O1"};
}

void Amplifer::receive()
{
    QByteArray data=serial_data->readAll();
    analysis->append(data);
}

void Amplifer::ConnectDevice(QMap<QString, QVariant> param)
{
    if(serial_data->isOpen())
    {
        serial_data->close();
        emit connectStatus("连接");
    }
    else
    {
        QString name=param["name"].toString();
        quint32 baudrate=param["baudrate"].toUInt();
        setBaudRate(baudrate);
        setPort(name);
        bool isok=serial_data->open(QIODevice::ReadWrite);
        if(isok)
        {
            stop();
            emit connectStatus("断开");
            emit connectSuccess();
        }
        else
        {
            emit error(0);
        }
    }

}

void Amplifer::serialErrorDeal(QSerialPort::SerialPortError error)
{
    if(error==QSerialPort::WriteError)
    {
        emit connectStatus("连接");
    }
}
void Amplifer::initDeivceParam()
{
    device_param.stop_bit=QSerialPort::OneStop;
    device_param.data_bit=QSerialPort::Data8;
    device_param.parity_bit=QSerialPort::NoParity;
    device_param.flow_control=QSerialPort::NoFlowControl;
}

void Amplifer::initSerialData()
{
    serial_data=new QSerialPort;
    serial_data->setStopBits(device_param.stop_bit);
    serial_data->setDataBits(device_param.data_bit);
    serial_data->setParity(device_param.parity_bit);
    serial_data->setFlowControl(device_param.flow_control);
}

void Amplifer::setSerialDataConnect()
{
    connect(serial_data,&QSerialPort::readyRead,this,&Amplifer::receive);
    connect(serial_data,&QSerialPort::errorOccurred,this,&Amplifer::serialErrorDeal);
}

void Amplifer::setAnalysisConnect()
{
    connect(analysis,&DataAnalysis::finishedEEGData,this,&Amplifer::readDataEEG);
}

void Amplifer::initConnetWidget()
{
    connectwidget=new ConnectWidget;
}

void Amplifer::setConnectConnect()
{
    connect(connectwidget,&ConnectWidget::connectDevice,this,&Amplifer::ConnectDevice);
    connect(this,&Amplifer::connectStatus,connectwidget,&ConnectWidget::setConnectStatus);
}

void Amplifer::init()
{
    //成员初始化
    eegdata=new EEGData;
    analysis=new DataAnalysis;
    encode=new Encode;
    initDeivceParam();
    initSerialData();
    initConnetWidget();
}

void Amplifer::setConnect()
{
    setSerialDataConnect();
    setAnalysisConnect();
    setConnectConnect();
}
