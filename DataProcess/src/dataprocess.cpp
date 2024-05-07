#include "dataprocess.h"
#include "math.h"
#define   PI  acos(-1)
#include "cmath"
#include "DSPFilters/Dsp.h"
#include "QDebug"
using namespace  DataProcess;
Filter::Filter()
{

}
void Filter::init(int channel_num,double fs,double cutoff_high, double cutoff_low)
{
    double band_width=cutoff_low-cutoff_high;
    double center_fre=cutoff_high+band_width/2;
    Dsp::SimpleFilter <Dsp::Butterworth::BandPass <4> > filter;
    filter.setup (4, fs,center_fre,band_width);
    double coefficient[24];
    for(int i=0;i<filter.getNumStages();i++)
    {
        coefficient[i*6+0]=filter[i].getB0();
        coefficient[i*6+1]=filter[i].getB1();
        coefficient[i*6+2]=filter[i].getB2();
        coefficient[i*6+3]=filter[i].getA0();
        coefficient[i*6+4]=filter[i].getA1();
        coefficient[i*6+5]=filter[i].getA2();
    }
    setChannelNum(channel_num);
    initW(4);    
    setCoefficient(coefficient,24);
}
void Filter::initW(int order)
{
    N_IIR=order/2;
    matrix_l.setSize({channel_num,N_IIR,3});
    matrix_h.setSize({channel_num,N_IIR,3});
    matrix_b.setSize({channel_num,order,3});
    for(int channel=0;channel<channel_num;channel++)
    {
        for(int N=0;N<N_IIR;N++)
        {
            matrix_l(channel,N,0)=0;
            matrix_l(channel,N,1)=0;
            matrix_l(channel,N,2)=0;
            matrix_h(channel,N,0)=0;
            matrix_h(channel,N,1)=0;
            matrix_h(channel,N,2)=0;
        }
        for(int N=0;N<order;N++)
        {
            matrix_b(channel,N,0)=0;
            matrix_b(channel,N,1)=0;
            matrix_b(channel,N,2)=0;
        }
    }
    coefficient_l.setSize({N_IIR,6});
    coefficient_h.setSize({N_IIR,6});
    coefficient_b.setSize({order,6});
}

void Filter::setChannelNum(int num)
{
     channel_num=num;
}

void Filter::setCoefficient(double *data, unsigned int len)
{
//    coefficient_l.load(data,len/2);
//    coefficient_h.load(data+len/2,len/2);
    coefficient_b.load(data,len);
}
void Filter::printCoefficient()
{
//    coefficient_l.printData();
//    coefficient_h.printData();
    coefficient_b.printData();
}
//y(n)=[b0+b1*x(n-1)+b2*x(n-2)]/1+a1*x(n-1)+a2*x(n-2);
double Filter::iir(int channel, double data)
{
    double temp=data;
    //带通
    for(int k=0;k<N_IIR*2;k++)
    {
        matrix_b(channel,k,0)=temp-coefficient_b(k,4)*matrix_b(channel,k,1)-coefficient_b(k,5)*matrix_b(channel,k,2);
        temp=coefficient_b(k,0)*matrix_b(channel,k,0)+coefficient_b(k,1)*matrix_b(channel,k,1)+coefficient_b(k,2)*matrix_b(channel,k,2);
        matrix_b(channel,k,2)=matrix_b(channel,k,1);
        matrix_b(channel,k,1)=matrix_b(channel,k,0);
    }

//    //低通
//    for(int k=0;k<N_IIR;k++)
//    {
//        matrix_l(channel,k,0)=temp-coefficient_l(k,4)*matrix_l(channel,k,1)-coefficient_l(k,5)*matrix_l(channel,k,2);
//        temp=coefficient_l(k,0)*matrix_l(channel,k,0)+coefficient_l(k,1)*matrix_l(channel,k,1)+coefficient_l(k,2)*matrix_l(channel,k,2);
//        matrix_l(channel,k,2)=matrix_l(channel,k,1);
//        matrix_l(channel,k,1)=matrix_l(channel,k,0);
//    }
//    //高通
//    for(int k=0;k<N_IIR;k++)
//    {
//        matrix_h(channel,k,0)=temp-coefficient_h(k,4)*matrix_h(channel,k,1)-coefficient_h(k,5)*matrix_h(channel,k,2);
//        temp=coefficient_h(k,0)*matrix_h(channel,k,0)+coefficient_h(k,1)*matrix_h(channel,k,1)+coefficient_h(k,2)*matrix_h(channel,k,2);
//        matrix_h(channel,k,2)=matrix_h(channel,k,1);
//        matrix_h(channel,k,1)=matrix_h(channel,k,0);
//    }
    return temp;
}
