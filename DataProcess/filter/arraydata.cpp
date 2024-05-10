#include "arraydata.h"
ArrayData::ArrayData(/* args */)
{
}

ArrayData::ArrayData(std::initializer_list<int> dims)
{
    setSize(dims);
}

void ArrayData::setSize(std::initializer_list<int> dims)
{
    this->dim=dims.size();
    size=(unsigned int *)malloc(sizeof (unsigned int)*dim);
    int i=0;
    int data_len=1;
    for(auto dim:dims)
    {
        this->size[i]=dim;
        i++;
        data_len*=dim;
    }
    data=malloc(sizeof (double)*data_len);
}

void ArrayData::load(void *data,unsigned int len)
{
    memcpy(this->data,data,sizeof (double)*len);
}

void ArrayData::printData()
{
    double *data=(double*)this->data;
    int data_len=1;
    for(int i=0;i<dim;i++)
    {
        data_len*=size[i];

    }
    for(int i=0;i<data_len;i++)
    {
        std::cout<<*data<<" ";
        data++;
        if((i+1)%size[dim-1]==0)
        {
             std::cout<<std::endl;
        }

    }
}
ArrayData::~ArrayData()
{
    free(data);
}
double& ArrayData::operator()(int index1,int index2,int index3)
{
    double *value=(double*)data;
    return value[index1*size[1]*size[2]+index2*size[2]+index3];
}

double& ArrayData::operator()(int index1, int index2)
{
    double *value=(double*)data;
    return value[index1*size[1]+index2];
}
