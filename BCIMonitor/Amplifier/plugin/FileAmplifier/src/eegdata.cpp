#include "eegdata.h"
#include "QDebug"
EEGData::EEGData()
{
    point_num=5;
    current_index=0;
    data=NULL;
}

EEGData::~EEGData()
{
    clear();
}
QList<QList<double>> EEGData::getData()
{
    QList<QList<double>> eeg_data;
    quint32 overlength=current_index-data_length;
    if(current_index==data_length)
    {
        current_index=0;
    }
    if(overlength<point_num)
    {
        for (quint8 i=0;i<overlength;i++)
        {
            QList<double> data;
            for(int j=0;j<channel_num;j++)
            {
                double value=this->data[current_index*channel_num+j];
                data.append(value);
            }
            current_index++;
            current_index%=data_length;
            eeg_data.append(data);
        }
        return eeg_data;
    }
    else
    {
        for (int i=0;i<point_num;i++)
        {
            QList<double> data;
            for(int j=0;j<channel_num;j++)
            {
                double value=this->data[current_index*channel_num+j];
                data.append(value);
            }
            current_index++;
            eeg_data.append(data);
        }
        return eeg_data;
    }

}

void EEGData::clear()
{
    if(data!=NULL)
    {
        free(data);
        this->data=NULL;
    }
}

void EEGData::setData(void *data,quint32 length,quint8 channel_num)
{
    clear();
    quint32 data_byte_size=length*channel_num*sizeof (double);
    this->data=(double*)malloc(data_byte_size);
    memcpy(this->data,data,data_byte_size);
    this->data_length=length;
    this->channel_num=channel_num;

}
