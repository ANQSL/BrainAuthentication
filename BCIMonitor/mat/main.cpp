#include <QCoreApplication>
#include "matread.h"
#include "QDebug"
int main(int argc, char *argv[])
{
    QString Dir=QString(argv[1]);
    QString channel_num=QString(argv[2]);
    QString point_num=QString(argv[3]);
//    QString Dir="D:/project/BrainAuthentication/BCIMonitor/build/debug/test/eegdata/lx/2024-04-22/8";
//    QString channel_num="32";
//    QString point_num="198790";
    MatRead matread;
    matread.setDataDim(channel_num.toUInt(),point_num.toUInt());
    matread.setDir(Dir);
    return 0;
}
