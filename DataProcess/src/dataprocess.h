#ifndef DATAPROCESS_H
#define DATAPROCESS_H
#include "iostream"
#include "vector"
#include "arraydata.h"
#include "QList"
namespace DataProcess {
class Filter;
};
class DataProcess::Filter
{

public:
    Filter();
    void init(int,double,double,double);
    QList<double> filter(QList<double>);
    ArrayData matrix_l;
    ArrayData matrix_h;
    ArrayData coefficient_l;
    ArrayData coefficient_h;

    ArrayData coefficient_b;

    ArrayData matrix_b;

    void printCoefficient();

    int N_IIR;

    double iir(int channel,double data);
private:
    void initW(int order);
    void setChannelNum(int num);
    void setCoefficient(double *data,unsigned int len);
    int channel_num;
};
#endif // DATAPROCESS_H
