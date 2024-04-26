#include "protocolsb.h"
#include "QDebug"
ProtocolsB::ProtocolsB()
{
       Encryption_init();
}

int ProtocolsB::findBufferHead(QByteArray data)
{
    if(data.isEmpty())
    {
        return 0;
    }
    QByteArray packet_head;
    packet_head.append(0xA1);
    packet_head.append(0x05);
    return data.indexOf(packet_head);
}

int ProtocolsB::findBufferEnd(QByteArray data)
{
    QByteArray packet_head;
    packet_head.append(0xA1);
    packet_head.append(0x05);
    if(data.size()<FRAMELEN+2)
    {
        return -1;
    }
    else
    {
        if(data[FRAMELEN]==char(0xA1)&&data[FRAMELEN+1]==char(0x05))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

QList<double> ProtocolsB::analysisEEGdata(QByteArray raw_data)
{
    //数据解密
   QList<double> channel_data;
   unsigned char *data=(unsigned char*)malloc(1030);
   memcpy(data,raw_data.data(),1030);
   SMS4Decrypt((ulong*)(data+7),1023,DERK);
   QByteArray decode_data;;
   decode_data.append((char*)data,1030);
   free(data);
   //数据转化
   for(int i=0;i<10;i++)
   {
       QByteArray _decode_data=decode_data.mid(0,103);
       decode_data.remove(0,103);
       QByteArray data_frame=_decode_data.right(96);
       for(int j=0;j<channel_num;j++)
       {
           DataTransformation data;
           data.buffer[0]=(data_frame.at(j*3+2));
           data.buffer[1]=data_frame.at(j*3+1);
           data.buffer[2]=data_frame.at(j*3);
           data.buffer[3]=00;
           quint32 value=data.data;
           double real_value=(value*1.0-8388608)/(8388608)*5000000/24;
           channel_data.append(real_value);
       }
   }
   return channel_data;
}

QList<double> ProtocolsB::analysisEEGdata(QByteArray raw_data, QList<double> &raw_channel_data,bool decode_status)
{
    //数据解密
   raw_channel_data.clear();
   QList<double> chart_channel_data;
   unsigned char *data=(unsigned char*)malloc(1030);
   memcpy(data,raw_data.data(),1030);
   if(decode_status)
   {
      SMS4Decrypt((ulong*)(data+7),1023,DERK);
   }
   QByteArray decode_data;
   decode_data.append((char*)data,1030);
   free(data);
   //数据转化
   for(int i=0;i<10;i++)
   {
       QByteArray _decode_data=decode_data.mid(0,103);
       decode_data.remove(0,103);
       QByteArray data_frame=_decode_data.right(96);
       for(int j=0;j<channel_num;j++)
       {
           DataTransformation data;
           data.buffer[0]=data_frame.at(j*3+2);
           data.buffer[1]=data_frame.at(j*3+1);
           data.buffer[2]=data_frame.at(j*3);
           data.buffer[3]=00;
           quint32 value=data.data;
           double real_value=(value*1.0-8388608)/8388608*5000000/24;
           chart_channel_data.append(real_value);
           raw_channel_data.append(value);
       }
   }
   return chart_channel_data;
}

quint16 ProtocolsB::getFrameLen()
{
     return 1030;
}

quint8 ProtocolsB::getChannelNum()
{
    return channel_num;
}
