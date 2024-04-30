#ifndef CCA_H
#define CCA_H
#define REFNUM 4
#define mydatalength2 5000
#include "QObject"
class CCA:public QObject
{
    Q_OBJECT
public:
    explicit CCA();
    void start(quint8);
    int Classify(double X[][mydatalength2],int channel_num);
    void append(QList<double>);
private:
     void init();
     double REF[REFNUM][4][mydatalength2];
     double ref_rate[REFNUM];
     double Caculate(double** X, double** Y, int p, int q, int n);
     double max(double *,int);

     double data[32][mydatalength2];

     quint64 current_data_num;
     quint8 mark;
     quint16  all_num;
     quint16  valid_num;
};

#endif // CCA_H
