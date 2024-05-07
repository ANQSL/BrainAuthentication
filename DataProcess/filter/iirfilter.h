#ifndef IIRFILTER_H
#define IIRFILTER_H
#include "arraydata.h"
class IIRFILTER
{
public:
    IIRFILTER();
    void initW(int order);
    void setChannelNum(int num);
    void setCoefficient(double *data,unsigned int len);
    ArrayData matrix_l;
    ArrayData matrix_h;

    ArrayData coefficient_l;
    ArrayData coefficient_h;

    void printCoefficient();

    int N_IIR;

    double iir(int channel,double data);
private:
    int channel_num;

};

#endif // IIRFILTER_H
