#ifndef IIRFILTER_H
#define IIRFILTER_H
#include<QString>
#include<QDebug>
class IIRFILTER
{
public:
    static const int N=11;
    int N_IIR=5;
    IIRFILTER();
    void initW();
    //0.5-70Hz的低通滤波 500Hz
    double b[5][3] = {
      {
         0.3601524803804,                 0,                 0
      },
      {
                       1,                 0,                -1
      },
      {
         0.3601524803804,                 0,                 0
      },
      {
                       1,                 0,                -1
      },
      {
                       1,                 0,                 0
      }
    };
    double a[5][3] = {
      {
                       1,                 0,                 0
      },
      {
                       1,   -1.991115168499,   0.9911549567301
      },
      {
                       1,                 0,                 0
      },
      {
                       1,  -0.7555790575051,   0.2767891866846
      },
      {
                       1,                 0,                 0
      }
    };

    double matrix_band[16][5][3];


    double iir(double *a, double *b, double *w, double xin, int N_IIR);
    double B_filter(int i,double xn);
    int n_N=20;
    double x[16][21];
    double y[16][21];

};

#endif // IIRFILTER_H
