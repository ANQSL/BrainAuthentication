#include <QApplication>
#include "bcimonitor.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BCIMonitor bciMonitor;
    bciMonitor.setFileMsg("lx",123);
    bciMonitor.show();
    return a.exec();
}
