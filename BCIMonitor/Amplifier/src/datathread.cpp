#include "datathread.h"

DataThread::DataThread(QObject *parent) : QThread(parent)
{
    this->destroyFlag=false;
    this->status=false;
}
void DataThread::run()
{
    while (1) {
        if(status&&(device!=NULL))
        {
            QList<double> raw_data=device->getRawData();
//            emit rawDataFinished(raw_data);
            QList<QList<double>> all_data=device->getChartData();
            int buf_num=all_data.size();
            for(int i=0;i<buf_num;i++){
                QList<double> data=all_data.at(i);
                emit rawDataFinished(data);
                data=filter.filterData(data);
                if(!data.isEmpty())
                {
                    emit readFinish(data);
                    if(destroyFlag)
                    {
                        destroyFlag=false;
                        return;
                    }
                }
            }
        }
        if(destroyFlag)
        {
            destroyFlag=false;
            return;
        }
        msleep(20);
    }
}

void DataThread::setDeivce(AmplifierDevice *device)
{
    this->device=device;
    filter.setChannelNum(device->getChannnelNum());

    filter.setEEGIndex(device->getEEGIndex()); //EEG全部通道索引
    filter.setMuscleIndex(device->getMuscleIndex()); //肌电通道索引
    filter.setBreathIndex(device->getBreathIndex()); //呼吸通道索引
    filter.setHeartIndex(device->getHeartIndex()); //心电通道索引
    filter.setSampleRate(device->getSampleRate());
//    qDebug()<<device->getEEGIndex();
//    qDebug()<<device->getHeartIndex();
}
void DataThread::setStatus(bool value)
{
    status = value;
}

void DataThread::destroy()
{
    destroyFlag = true;
}

bool DataThread::getStatus() const
{
    return status;
}

void DataThread::clearFilter()
{
    filter.init();
}
