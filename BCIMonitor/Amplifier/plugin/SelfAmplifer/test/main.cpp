
#include "QApplication"
#include "selfamplifer.h"
#include "QWidget"
int main(int args,char** argv)
{
    QApplication app(args,argv);
    SelfAmplifer w;
    w.getConnectWidget()->show();
    return  app.exec();
}
