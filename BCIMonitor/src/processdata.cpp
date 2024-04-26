#include "processdata.h"
#include "QDebug"
ProcessData::ProcessData(QObject *parent) : QObject(parent)
{
}

void ProcessData::setDownRate(quint16 value)
{
    downrate=value;
}
void ProcessData::setSrate(const quint16 &value)
{
    down_sample = value/downrate;

}

void ProcessData::seteeggame_index(QList<uint8_t> index)
{
    eeggame_index = index;
}


void ProcessData::setMuscleIndex(QList<uint8_t> index)
{
    muscle_index = index;
}

void ProcessData::setBreathIndex(QList<uint8_t> index)
{
    breath_index = index;
}

void ProcessData::setHeartIndex(QList<uint8_t> index)
{
    heart_index = index;
}


void ProcessData::clear()
{
    data.clear();
}




void ProcessData::receiveData(QList<double> value)
{
    //BP的索引
//    int label_index[12]={2,3,13,7,17,21,24,26,27,28,29,30};
    data.append(value);      
    if(data.size()>=down_sample)
    {
        //eeg信号,12个通道
        QString eeggame_data="MsgType=Curve,Points=";
        for(int i=0;i<eeggame_index.size();i++)
        {
             double channel_data=0;
             for(int j=0;j<down_sample;j++)
             {
                channel_data+=data[j][eeggame_index[i]];
             }
             channel_data/=down_sample;
             eeggame_data+=QString::number(channel_data)+",";
        }
        eeggame_data+="MsgEnd";

        //肌电muscle
        QString muscle_data="MsgType=Muscle,Points=";
        for(int i=0;i<muscle_index.size();i++)
        {
             double channel_data=0;
             for(int j=0;j<down_sample;j++)
             {
                channel_data+=data[j][muscle_index[i]];
             }
             channel_data/=down_sample;
             muscle_data+=QString::number(channel_data)+",";
        }
        muscle_data+="MsgEnd";

        //呼吸breath
        QString breath_data="MsgType=Breath,Points=";
        for(int i=0;i<breath_index.size();i++)
        {
             double channel_data=0;
             for(int j=0;j<down_sample;j++)
             {
                channel_data+=data[j][breath_index[i]];
             }
             channel_data/=down_sample;
             breath_data+=QString::number(channel_data)+",";
        }
        breath_data+="MsgEnd";

        //心电heart
        QString heart_data="MsgType=Heart,Points=";
        for(int i=0;i<heart_index.size();i++)
        {
             double channel_data=0;
             for(int j=0;j<down_sample;j++)
             {
                channel_data+=data[j][heart_index[i]];
             }
             channel_data/=down_sample;
             heart_data+=QString::number(channel_data)+",";
        }
        heart_data+="MsgEnd";

        data.remove(0,down_sample);
        emit downData(eeggame_data);
        emit downData(muscle_data);
        emit downData(breath_data);
        emit downData(heart_data);
//        emit downData(other_data);
    }

}




