#include "ssvepclassify.h"
SSVEPClassify::SSVEPClassify(QObject *parent) : QObject(parent)
{
    classifier=new CCA;
}

double SSVEPClassify::Classify(double X[][mydatalength2], int channel_num)
{
    CCA* cca=(CCA*)classifier;
    return cca->Classify(X,channel_num);
}
