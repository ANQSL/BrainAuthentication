#include "dataprocess.h"
int main(int args,char **argv)
{
    DataProcess::Filter filter;
    filter.init(32,1000,1,30);
    filter.printCoefficient();
}
