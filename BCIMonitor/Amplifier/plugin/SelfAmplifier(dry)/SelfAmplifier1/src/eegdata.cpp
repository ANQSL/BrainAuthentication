#include "eegdata.h"
#include "QDebug"
EEGData::EEGData()
{
    point_num=100;
}

void EEGData::append(QList<double> data)
{
    mutex.lock();
    this->data.append(data);
    mutex.unlock();
//    qDebug()<<data;
}

QList<QList<double>> EEGData::getData()
{
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
