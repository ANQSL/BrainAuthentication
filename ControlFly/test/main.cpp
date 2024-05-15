#include "QCoreApplication"
#include "controlfly.h"
class Test:public QObject
{
    void timerEvent(QTimerEvent *event)
    {
        if(control.connectStatus())
        {
            quint8 data=rand()%(4)+1;
            control.command(data);
        }
    }
private:
    ControlFly control;
};
int main(int args,char** argv)
{
    QCoreApplication app(args,argv);
    Test test;
    test.startTimer(3000);
    return  app.exec();
}
