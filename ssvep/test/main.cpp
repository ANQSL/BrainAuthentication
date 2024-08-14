#include "ssvep.h"
#include "QApplication"
int main(int args,char **argv)
{
    QApplication app(args,argv);
//    HANDLE hProcess = GetCurrentProcess();
//    SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
    SSVEP ssvep;
    ssvep.show();
    return app.exec();
}
