#include "QApplication"
#include "ssvepwidget.h"
int main(int args,char* *argv)
{
    QApplication app(args,argv);
    SSVEPWidget ssvepwidget;
//    ssvepwidget.show();
    return app.exec();
}
