#include "dataanalysis.h"
#include "QDebug"
DataAnalysis::DataAnalysis(QObject *parent) : QObject(parent)
{

}

void DataAnalysis::append(QByteArray data)
{
    this->receive_data.append(data);
    analysis();
}

void DataAnalysis::analysis()
{
    if(receive_data.isEmpty())
    {
        return;
    }
    while(findBufferHead())
    {
        QByteArray buffer;
        if(findBufferEnd(buffer))
        {
            if(buffer[3]==char(0x00))
            {
//                qDebug()<<buffer.size();
                quint16 buffer_len=quint16(buffer[1]<<8)+buffer[2];
                QByteArray eegbuffer=buffer.mid(12,buffer_len-3);
                analysisEEG(eegbuffer);

            }
        }
        else
        {
            break;
        }
    }
}

bool DataAnalysis::findBufferHead()
{
    for(int i=0;i<receive_data.size();)
    {
         if(receive_data[i]!=char(0xBE))
         {
             receive_data.remove(i,1);
         }
         else
         {
             break;
         }
    }
    if(receive_data.isEmpty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DataAnalysis::findBufferEnd(QByteArray &buffer)
{
    if(receive_data.size()<=3)
    {
        return false;
    }
    quint16 buffer_len=quint16(receive_data[1]<<8)+receive_data[2];
    if(receive_data.size()>=buffer_len&&receive_data[buffer_len-1]==char(0xEB))
    {
        buffer=receive_data.left(buffer_len);
        receive_data.remove(0,buffer_len);
        return true;
    }
    else
    {
        return false;
    }
}

void DataAnalysis::analysisEEG(QByteArray buffer)
{
    QList<bool> off_indicate;
    for(int i=0;i<eeg_sample_num;i++)
    {
        QList<double> eeg_data;
        for(int j=0;j<eeg_num;j++)
        {
            QByteArray data=buffer.mid(i*16+4*j,(j+1)*4);
            bool isok;
            double value;
            analysisEEGItem(data,value,isok);
            eeg_data.append(value);
            if((eeg_sample_num-i)==1)
            {
                off_indicate.append(isok);
            }
        }
        emit finishedEEGData(eeg_data);
    }
}
void DataAnalysis::analysisEEGItem(QByteArray buffer,double &value,bool & off_indicate)
{
    QByteArray eeg(4,'\0');
    eeg[0]=0;
    eeg[1]=buffer[1];
    eeg[2]=buffer[2];
    eeg[3]=buffer[3];
    uint32_t receiver_data=0;
    memcpy(&receiver_data,eeg,4);
    receiver_data=receiver_data>>8;
    int eeg_data=receiver_data-8388608;
    value=eeg_data*0.1;
    off_indicate=buffer[0]&0x01;
}
