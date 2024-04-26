#include "selfamplifier.h"
#include "QDebug"
SelfAmplifier::SelfAmplifier()
{
    init();
    setConnect();
}

SelfAmplifier::~SelfAmplifier()
{
    if(serial_data->isOpen())
    {
       stop();
    }
    data_analysis->destory();
    QThread::msleep(20);
    delete serial_data;
    delete eegdata;
    delete data_analysis;
    delete connectwidget;
}
void SelfAmplifier::setPort(QString name)
{
    serial_data->setPortName(name);
    device_param.serial_name=name;
}

void SelfAmplifier::setBaudRate(quint32 band_rate)
{
    bool isok=serial_data->setBaudRate(band_rate);
    if(isok)
    {
        device_param.baud_rate=band_rate;
    }
    else
    {
    }
}

void SelfAmplifier::append(QList<double> data)
{
    if(data_status)
    {
        eegdata->append(data);
    }
}

void SelfAmplifier::start()
{
    this->data_status=true;
//    serial_data->clear();
    eegdata->clear();
    QByteArray start=encode.start();
    serial_data->write(start);
}

void SelfAmplifier::stop()
{
    this->data_status=false;
    QByteArray stop=encode.stop();
    serial_data->write(stop);
}

QList<QList<double>> SelfAmplifier::getArrayData()
{
    QList<QList<double>> data=eegdata->getData();
    return data;
}

QList<uint8_t> SelfAmplifier::getEEGGameIndex()
{
    return {};
}

QList<uint8_t> SelfAmplifier::getEEGIndex()
{
    return {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
}

QList<uint8_t> SelfAmplifier::getMuscleIndex()
{
    return {};
}

QList<uint8_t> SelfAmplifier::getBreathIndex()
{
    return {};
}

QList<uint8_t> SelfAmplifier::getHeartIndex()
{
    return {};
}

bool SelfAmplifier::connectStatus()
{
    return serial_data->isOpen();
}
QWidget *SelfAmplifier::getConnectWidget()
{
    return connectwidget;
}

QList<double> SelfAmplifier::getOneData()
{
    QList<double> data;
    return data;
}
QStringList SelfAmplifier::getChannelName()
{
    return {"C4","P2","CP6","FC6",
        "AF4","FCZ","FZ","FP2",
        "PZ","P1","POZ","CP5",
        "C3","FC5","AF3","FP1"};
}

quint8 SelfAmplifier::getChannnelNum()
{
    return 16;
}

quint16 SelfAmplifier::getSampleRate()
{
    return 250;
}
QWidget *SelfAmplifier::getConfigWidget()
{
    return NULL;
}
void SelfAmplifier::ConnectDevice(QMap<QString, QVariant> param)
{
    if(serial_data->isOpen())
    {
        serial_data->close();
        data_analysis->destory();
        this->connectwidget->setConnectStatus("连接");
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
            data_analysis->start();
            this->connectwidget->hide();
            this->connectwidget->setConnectStatus("断开");
        }
        else
        {
            this->connectwidget->showConnectMsg("连接失败");
        }
    }

}

void SelfAmplifier::serialErrorDeal(QSerialPort::SerialPortError error)
{
    if(error==QSerialPort::ResourceError)
    {
        data_analysis->destory();
    }
}
void SelfAmplifier::initDeivceParam()
{
    device_param.stop_bit=QSerialPort::OneStop;
    device_param.data_bit=QSerialPort::Data8;
    device_param.parity_bit=QSerialPort::NoParity;
    device_param.flow_control=QSerialPort::NoFlowControl;
}

void SelfAmplifier::initSerialData()
{
    serial_data=new QSerialPort;
    this->data_status=false;
    serial_data->setStopBits(device_param.stop_bit);
    serial_data->setDataBits(device_param.data_bit);
    serial_data->setParity(device_param.parity_bit);
    serial_data->setFlowControl(device_param.flow_control);
}

void SelfAmplifier::setSerialDataConnect()
{
    connect(serial_data,&QSerialPort::errorOccurred,this,&SelfAmplifier::serialErrorDeal);
}

void SelfAmplifier::initAnalysis()
{
    data_analysis=new DataAnalysis;
    data_analysis->setSerial(serial_data);
}

void SelfAmplifier::setAnalysisConnect()
{
    connect(data_analysis,&DataAnalysis::finishedEEGData,this,&SelfAmplifier::append);
}

void SelfAmplifier::initConnetWidget()
{
    connectwidget=new ConnectWidget;
}

void SelfAmplifier::setConnectConnect()
{
    connect(connectwidget,&ConnectWidget::connectDevice,this,&SelfAmplifier::ConnectDevice);
}

void SelfAmplifier::init()
{
    qRegisterMetaType<QList<double>>("QList<double>");
    qRegisterMetaType<QList<bool>>("QList<bool>");
    qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
    //成员初始化
    eegdata=new EEGData;
    initDeivceParam();
    initSerialData();
    initAnalysis();
    initConnetWidget();
}

void SelfAmplifier::setConnect()
{
    setSerialDataConnect();
    setAnalysisConnect();
    setConnectConnect();
}
