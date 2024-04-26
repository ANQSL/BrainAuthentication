#include "amplifer.h"
#include "QThread"
#include "QDebug"
#include "QApplication"
#include "QWidget"
int main(int args,char ** argv)
{
    QApplication app(args,argv);
    Amplifer amplifer;
    QWidget *widget=amplifer.getConnectWidget();
    widget->show();
    return app.exec();
}
