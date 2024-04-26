#include "eegdata.h"
#include "QDebug"
EEGData::EEGData()
{
    point_num=100;
}

void EEGData::append(QList<double> data)
{
//    qDebug()<<"list:数据"<<data;
//    qDebug()<<"vector:数据"<<data;
    mutex.lock();
    this->data.append(data);
    mutex.unlock();
}

QList<QList<double>> EEGData::getData()
{

//    QList<QList<double>> eeg_data;
//    if(this->data.size()<point_num*16)
//    {
//        return eeg_data;
//    }
//    mutex.lock();
//    for (int i=0;i<point_num;i++)
//    {
//        QList<double> data;
//        for(int j=0;j<16;j++)
//        {

//            double value=this->data.takeAt(0);

//            data.append(value);
//        }
//        eeg_data.append(data);
//    }
//    mutex.unlock();
//    qDebug()<<this->data.size();
    QList<QList<double>>  eegdata;
    mutex.lock();
    if(!data.isEmpty())
    {
       eegdata=data;
       this->data.clear();
    }
    mutex.unlock();
    return eegdata;
}

void EEGData::clear()
{
    data.clear();
}
