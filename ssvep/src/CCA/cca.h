#ifndef CCA_H
#define CCA_H
#define REFNUM 8
#define mydatalength2 1950
class CCA
{
public:
    explicit CCA();
    int Classify(double X[][mydatalength2],int channel_num);
private:
     void init();
     double REF[REFNUM][4][mydatalength2];
     double ref_rate[REFNUM];
     double Caculate(double** X, double** Y, int p, int q, int n);
     double max(double *,int);
};

#endif // CCA_H
