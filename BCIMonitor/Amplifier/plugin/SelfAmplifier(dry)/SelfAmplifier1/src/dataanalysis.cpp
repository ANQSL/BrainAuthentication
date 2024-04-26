#include "dataanalysis.h"
#include "QDebug"
#include "iostream"
#include "QEventLoop"
#include "QTimer"
const static int ADC=8388608;
const static double BAS_VOLTAGE=4.5;
const static int EEG_CIR_GAIN=12;
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
    while (buffer.size()>=FRAMELEN+HEADLEN) {
        QByteArray frame=readFrame();
        if(!frame.isEmpty())
        {
            analysisEEG(frame);

        }
    }
}

bool DataAnalysis::findBufferHead()
{
    char head[2];
    head[0]=0xAA;
    head[1]=0x55;
    if((buffer[0]==char(0X3E))&&(buffer[1]==char(0x46)&&(buffer[2]==char(0x52))&&(buffer[3]==char(0x90))))
    {
        return true;
    }
    else
    {
        quint16 buffer_size=buffer.size();
        for(int i=0;i<buffer_size;i++)
        {
            if((buffer[i]==char(0X3E))&&(buffer[i+1]==char(0x46)&&(buffer[i+2]==char(0x52))&&(buffer[i+3]==char(0x90))))
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
    //数据帧
    QByteArray data_buffer=frame.mid(12);
    int data_len=data_buffer.size();
    //保存数据
    QVector<QVector<double>> data(4);
    int frame_order=0;
    for(int i=0;i<data_len;i+=3)
    {
        if((i)%48==0&&i!=0)
        {
            frame_order++;
        }
        {
            //拼接数据
            uint32_t encode=0;
            encode+=uint32_t(data_buffer[i]<<16);
            encode+=uint16_t(data_buffer[i+1]<<8);
            encode+=uint8_t(data_buffer[i+2]);
            //计算电压值
            if(encode>ADC)
            {
                encode=(encode-2*ADC);
            }
            double value=encode*BAS_VOLTAGE*1000*1000/ADC/EEG_CIR_GAIN;
            data[frame_order].append(value);
        }
    }
    for(auto value:data)
    {
        emit finishedEEGData(value.toList());
    }

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
        if(buffer.size()>=FRAMELEN+HEADLEN)
        {
            if((buffer[204]==char(0X3E))&&(buffer[205]==char(0x46)&&(buffer[206]==char(0x52))&&(buffer[207]==char(0x90))))
            {
                QByteArray frame=buffer.mid(0,FRAMELEN);
                buffer.remove(0,FRAMELEN);
                return frame;
            }
            else
            {
                buffer.remove(0,1);
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
        this->buffer.clear();
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
