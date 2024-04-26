#include "dataanalysis.h"
#include "QDebug"
#include "iostream"
#include "QEventLoop"
#include "QTimer"
DataAnalysis::DataAnalysis(QObject *parent) : QThread(parent)
{
    this->status=false;
}

void DataAnalysis::setSerial(QSerialPort *serial)
{
    this->serial=serial;
}

void DataAnalysis::start()
{
    QThread::start(QThread::HighPriority);
    this->status=true;
}

void DataAnalysis::destory()
{
    this->status=false;
}

void DataAnalysis::append(QByteArray data)
{
    this->buffer.append(data);
}
void DataAnalysis::analysis()
{
    while (buffer.size()>=FRAMELEN+2) {
        QByteArray frame=readFrame();
        if(!frame.isEmpty())
        {
            analysisEEG(frame);
//            frames.append(frame);
//            if(frames.size()==FRAMELEN*25)
//            {
//                analysisEEG()
//                QList<QList<double>> data= analysisEEG(frames);
//            }

        }
    }
}

bool DataAnalysis::findBufferHead()
{
    char head[2];
    head[0]=0xAA;
    head[1]=0x55;
    if((buffer[0]==char(0XAA))&&(buffer[1]==char(0x55)))
    {
        return true;
    }
    else
    {
        quint16 buffer_size=buffer.size();
        for(int i=0;i<buffer_size;i++)
        {
            if(buffer[i]==char(0xAA)&&(buffer[i+1]==char(0x55)))
            {
                buffer.remove(0,i);
                return true;
            }
        }
        return false;
    }
}

void DataAnalysis::analysisEEG(QByteArray frame)
{
    QList<double> data;
    for(int i=3;i<51;i+=3)
    {
        int value=0;
        value=(unsigned char)(frame[i]);
        value=value^0x80;
        value<<=8;
        value|=(unsigned char)(frame[i+1]);
        value<<=8;
        value|=(unsigned char)(frame[i+2]);
        double voltage_value=(value-8388608)*0.0044465;
        data.append(voltage_value);
    }
    data=reverse(data);
    emit finishedEEGData(data);
}
//QList<QList<double>> DataAnalysis::analysisEEG(QByteArray frame)
//{
//    QList<QList<double>> value;
//    QList<double> data;
//    if(frame.size()<51)
//    {
//        return value;
//    }
//    value.append(analysisEEG(frame.left(int(25/2)*FRAMELEN)));
//    value.append(analysisEEG(frame.right((int(25/2)+1)*FRAMELEN)));
//    for(int i=3;i<51;i+=3)
//    {
//        int value=0;
//        value=(unsigned char)(frame[i]);
//        value=value^0x80;
//        value<<=8;
//        value|=(unsigned char)(frame[i+1]);
//        value<<=8;
//        value|=(unsigned char)(frame[i+2]);
//        double voltage_value=(value-8388608)*0.0044465;
//        data.append(voltage_value);
//    }
//    data=reverse(data);
//    value.append(data);
//    return value;
//}
void DataAnalysis::run()
{
    while (1) {
        if(status)
        {
            if(readData())
            {
                analysis();
            }

        }
        else {
            break;
        }
        msleep(20);
    }
}
QByteArray DataAnalysis::readFrame()
{
    if(findBufferHead())
    {
        if(buffer.size()>=FRAMELEN+2)
        {
            if(buffer[51]==char(0XAA)&&(buffer[52]==char(0x55)))
            {
                QByteArray frame=buffer.mid(0,FRAMELEN);
                buffer.remove(0,FRAMELEN);
                return frame;
            }
            else
            {
                buffer.remove(0,2);
                return "";
            }
        }
        else
        {
            return "";
        }

    }
    else
    {
        return "";
    }
}

bool DataAnalysis::readData()
{
    bool isok=serial->waitForReadyRead(1);
    if(isok)
    {
        QByteArray data=serial->readAll();
        this->buffer.append(data);
        return true;
    }
    else
    {
        return false;
    }
}

QList<double> DataAnalysis::reverse(QList<double> data)
{
    int len=data.size();
    for(int i=0;i<len/2;i++)
    {
        double a=data[i];
        double b=data[len-1-i];
        data[i]=b;
        data[len-1-i]=a;
    }
    return data;
}
