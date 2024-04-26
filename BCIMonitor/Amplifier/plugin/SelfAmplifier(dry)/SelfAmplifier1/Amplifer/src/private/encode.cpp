#include "encode.h"

Encode::Encode()
{

}

QByteArray Encode::start()
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
    buffer[12]=0xAA;
    buffer[13]=0x38;
    buffer[14]=0x83;
    buffer[15]=0xEB;
    return buffer;
}

QByteArray Encode::stop()
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
    buffer[12]=0xBB;
    buffer[13]=0x49;
    buffer[14]=0x80;
    buffer[15]=0xEB;
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
