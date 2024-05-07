#ifndef ARRAY_H
#define ARRAY_H
#include "iostream"
class ArrayData
{
private:
    /* data */
    void *data;
    unsigned int *size;
    unsigned short int dim;
public:
    ArrayData(/* args */);
    ArrayData(std::initializer_list<int> dims);
    void setSize(std::initializer_list<int> dims);
    void load(void *data,unsigned int len);
    void printData();
    ~ArrayData();
    double& operator()(int,int,int);
    double& operator()(int,int);
};
#endif
