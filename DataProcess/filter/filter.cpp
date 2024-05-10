

#define DLLEXPORT extern "C" __declspec(dllexport)

#include "iirfilter.h"
IIRFILTER delta;
IIRFILTER theta;
IIRFILTER alpha;
IIRFILTER beta;
IIRFILTER gamma;
double *data=NULL;
DLLEXPORT void setChannelNum(int num)
{
    delta.setChannelNum(num);
    theta.setChannelNum(num);
    alpha.setChannelNum(num);
    beta.setChannelNum(num);
    gamma.setChannelNum(num);
}

DLLEXPORT void setCoefficient(double *coeff,int order)
{
    delta.initW(order);
    theta.initW(order);
    alpha.initW(order);
    beta.initW(order);
    gamma.initW(order);
    delta.setCoefficient(coeff,order*6);
    theta.setCoefficient(coeff+24,order*6);
    alpha.setCoefficient(coeff+24*2,order*6);
    beta.setCoefficient(coeff+24*3,order*6);
    gamma.setCoefficient(coeff+24*4,order*6);
//    delta.printCoefficient();
//    theta.printCoefficient();
//    alpha.printCoefficient();
//    beta.printCoefficient();
//    gamma.printCoefficient();

}
DLLEXPORT double* butter(double*arr,int channel_num,int point_num)
{

    data=(double*)malloc(sizeof (double)*channel_num*point_num*5);
    for(int channel_index=0;channel_index<channel_num;channel_index++)
    {
       for(int sample_index=0;sample_index<point_num;sample_index++)
       {
            data[channel_index*point_num*5+sample_index*5]=delta.iir(channel_index,arr[channel_index*point_num+sample_index]);
            data[channel_index*point_num*5+sample_index*5+1]=theta.iir(channel_index,arr[channel_index*point_num+sample_index]);
            data[channel_index*point_num*5+sample_index*5+2]=alpha.iir(channel_index,arr[channel_index*point_num+sample_index]);
            data[channel_index*point_num*5+sample_index*5+3]=beta.iir(channel_index,arr[channel_index*point_num+sample_index]);
            data[channel_index*point_num*5+sample_index*5+4]=gamma.iir(channel_index,arr[channel_index*point_num+sample_index]);
       }
    }
    return  data;
}
DLLEXPORT void clear()
{
    free(data);
    data=NULL;
}
