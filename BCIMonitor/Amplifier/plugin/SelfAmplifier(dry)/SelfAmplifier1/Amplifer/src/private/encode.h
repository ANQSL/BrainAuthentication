#ifndef ENCODE_H
#define ENCODE_H

#include "QByteArray"
class Encode
{
public:
    Encode();
    QByteArray start();
    QByteArray stop();
    QByteArray EEGSampleRate(int);
    char computeParityBit(QByteArray); 
};

#endif // ENCODE_H
