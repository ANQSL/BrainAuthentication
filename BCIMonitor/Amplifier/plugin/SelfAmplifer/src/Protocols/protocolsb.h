#ifndef PROTOCOLSB_H
#define PROTOCOLSB_H

#include <QWidget>
#include "protocols.h"

extern "C" {

#include "sms4.h"

}
#define FRAMELEN 1030
class ProtocolsB : public Protocols
{
    typedef  union data_transformation
    {
        char buffer[4];
        quint32 data;
    }DataTransformation;
public:
    ProtocolsB();
    int findBufferHead(QByteArray)override;
    int findBufferEnd(QByteArray)override;
    QList<double> analysisEEGdata(QByteArray)override;
    QList<double> analysisEEGdata(QByteArray,QList<double> &data,bool decode_status);

    quint16 getFrameLen()override;
    quint8 getChannelNum()override;
private:
    quint8 channel_num=32;
    //缓存数据不足一帧
    quint16 data_index=0;
};

#endif // PROTOCOLSB_H
