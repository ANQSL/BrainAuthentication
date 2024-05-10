#include "iirfilter.h"
IIRFILTER::IIRFILTER()
{
}
void IIRFILTER::initW(int order)
{
    N_IIR=order/2;

    matrix_l.setSize({channel_num,N_IIR,4});
    matrix_h.setSize({channel_num,N_IIR,4});
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
            matrix_l(channel,N,3)=0;
            matrix_h(channel,N,3)=0;
        }
    }
    coefficient_l.setSize({N_IIR,6});
    coefficient_h.setSize({N_IIR,6});


}

void IIRFILTER::setChannelNum(int num)
{
    channel_num=num;
}

void IIRFILTER::setCoefficient(double *data, unsigned int len)
{
    coefficient_l.load(data,len/2);
    coefficient_h.load(data+len/2,len/2);
}

void IIRFILTER::printCoefficient()
{
   coefficient_l.printData();
   coefficient_h.printData();
}

double IIRFILTER::iir(int channel, double data)
{


    double temp=data;
//    for(int k=0;k<N_IIR;k++)
//    {
//        double output_sum=coefficient_l(k,4)*matrix_l(channel,k,2)+coefficient_l(k,5)*matrix_l(channel,k,3);
//        double input_sum=coefficient_l(k,0)*temp+coefficient_l(k,1)*matrix_l(channel,k,0)+coefficient_l(k,2)*matrix_l(channel,k,1);
//        double this_input=temp;
//        temp=input_sum-output_sum;

//        matrix_l(channel,k,3)=matrix_l(channel,k,2);
//        matrix_l(channel,k,2)=temp;

//        matrix_l(channel,k,1)=matrix_l(channel,k,0);
//        matrix_l(channel,k,0)=this_input;
//    }
//    for(int k=0;k<N_IIR;k++)
//    {
//        double output_sum=coefficient_h(k,4)*matrix_h(channel,k,2)+coefficient_h(k,5)*matrix_h(channel,k,3);
//        double input_sum=coefficient_h(k,0)*temp+coefficient_h(k,1)*matrix_h(channel,k,0)+coefficient_h(k,2)*matrix_h(channel,k,1);
//        double this_input=temp;
//        temp=input_sum-output_sum;

//        matrix_h(channel,k,3)=matrix_h(channel,k,2);
//        matrix_h(channel,k,2)=temp;

//        matrix_h(channel,k,1)=matrix_h(channel,k,0);
//        matrix_h(channel,k,0)=this_input;
//    }
    for(int k=0;k<N_IIR;k++)
    {
        matrix_l(channel,k,0)=temp-coefficient_l(k,4)*matrix_l(channel,k,1)-coefficient_l(k,5)*matrix_l(channel,k,2);
        temp=coefficient_l(k,0)*matrix_l(channel,k,0)+coefficient_l(k,1)*matrix_l(channel,k,1)+coefficient_l(k,2)*matrix_l(channel,k,2);
        matrix_l(channel,k,2)=matrix_l(channel,k,1);
        matrix_l(channel,k,1)=matrix_l(channel,k,0);
    }
    for(int k=0;k<N_IIR;k++)
    {
        matrix_h(channel,k,0)=temp-coefficient_h(k,4)*matrix_h(channel,k,1)-coefficient_h(k,5)*matrix_h(channel,k,2);
        temp=coefficient_h(k,0)*matrix_h(channel,k,0)+coefficient_h(k,1)*matrix_h(channel,k,1)+coefficient_h(k,2)*matrix_h(channel,k,2);
        matrix_h(channel,k,2)=matrix_h(channel,k,1);
        matrix_h(channel,k,1)=matrix_h(channel,k,0);
    }
    return temp;
}


