#include "encode.h"

Encode::Encode()
{

}

QByteArray Encode::start()
{
    QByteArray buffer(10,'\0');
    buffer[0]=0x45;
    buffer[1]=0x4B;
    buffer[2]=0x55;
    buffer[3]=0x9F;
    buffer[4]=0x03;
    buffer[5]=0x00;
    buffer[6]=0x00;
    buffer[7]=0x00;
    buffer[8]=0x0D;
    buffer[9]=0x0A;
    return buffer;
}

QByteArray Encode::stop()
{
    QByteArray buffer(10,'\0');
    buffer[0]=0x45;
    buffer[1]=0x4B;
    buffer[2]=0x55;
    buffer[3]=0x9F;
    buffer[4]=0x04;
    buffer[5]=0x00;
    buffer[6]=0x00;
    buffer[7]=0x00;
    buffer[8]=0x0D;
    buffer[9]=0x0A;
    return buffer;
}

QByteArray Encode::EEGSampleRate(int rate)
{
    QByteArray buffer(16,'\0');
    buffer[0]=0xBE;
    buffer[1]=0x00;
    buffer[2]=0x10;
    buffer[3]=0x03;
    buffer[4]=0x56;
    buffer[5]=0x58;
    buffer[6]=0x59;
    buffer[7]=0x56;
    buffer[8]=0x58;
    buffer[9]=0x59;
    buffer[10]=0x56;
    buffer[11]=0x59;
    buffer[12]=rate;
    char parity_bit=computeParityBit(buffer);
    buffer[13]=parity_bit;
    buffer[14]=0x21;
    buffer[15]=0xEB;
    return buffer;
}

char Encode::computeParityBit(QByteArray data)
{
    qint16 sum=0;
    for(auto bit:data)
    {
        sum+=bit;
    }
    char parity_bit=sum;
    return parity_bit;
}
