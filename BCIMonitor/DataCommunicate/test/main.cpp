#include "datacommunicate.h"
#include "QApplication"
#include "QThread"
int main(int args,char** argv)
{
    QApplication app(args,argv);
    DataCommunicate datasend;
    datasend.setSrate(250);
    datasend.start();
    datasend.buildConnection();
    for(int i=0;i<2500;i++)
    {
        QList<double> data;
        for(int j=0;j<32;j++)
        {
           data.append(i+1);
        }
        datasend.append(data);
        QThread::usleep(10);
    }

    return  app.exec();
}
