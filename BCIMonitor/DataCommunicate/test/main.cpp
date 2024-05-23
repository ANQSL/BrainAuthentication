#include "datacommunicate.h"
#include "QApplication"
#include "QThread"
int main(int args,char** argv)
{
    QApplication app(args,argv);
    DataCommunicate datasend;
    datasend.setSrate(1000);
    datasend.start();
//    datasend.buildConnection();
    for(int i=0;i<5000;i++)
    {
        QList<double> data;
        for(int j=0;j<32;j++)
        {
           data.append(i*32+j);
        }
        datasend.append(data);
        QThread::usleep(1);
    }

    return  app.exec();
}
