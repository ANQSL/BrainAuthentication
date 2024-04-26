#include "fileamplifier.h"
#include "QApplication"
int main(int args,char** argv)
{
    QApplication app(args,argv);
    FIleAmplifier w;
    w.getConnectWidget()->show();
    return  app.exec();
}
