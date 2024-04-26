#include "eegdata.h"
#include "QDebug"
EEGData::EEGData()
{

}

void EEGData::append(QList<double> data,QList<bool> off_indicate)
{
    this->data.append(data);
    this->off_indicate=off_indicate;
//    qDebug()<<data;
//    qDebug()<<off_indicate;
//    qDebug()<<this->data;
}

QList<QList<double>> EEGData::getData()
{
    QList<QList<double>> eeg_data;
    for (int i=0;i<5;i++)
    {
        QList<double> data;
        for(int j=0;j<16;j++)
        {
            double value=this->data.takeAt(i*16+j);
            data.append(value);
        }
        eeg_data.append(data);
    }

    return eeg_data;
}
