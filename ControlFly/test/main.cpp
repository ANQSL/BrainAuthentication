#include "QApplication"
#include "controlfly.h"
#include "QImage"
#include "iostream"
#include "flycontrolwidget.h"
#include "controlfly.h"
#include "QTimer"
#include "QKeyEvent"
#include "fstream"
#include "h264decoder.hpp"
class Test:public QWidget
{
public:
    Test()
    {
        control.showControlWidget();
    }
    void keyPressEvent(QKeyEvent *event)
    {
        if(event->key()==Qt::Key_0)
        {
           control.sendCommand(0);
        }
        if(event->key()==Qt::Key_1)
        {
           control.sendCommand(1);
        }
        if(event->key()==Qt::Key_2)
        {
           control.sendCommand(2);
        }
        if(event->key()==Qt::Key_3)
        {
           control.sendCommand(3);
        }
        if(event->key()==Qt::Key_4)
        {
           control.sendCommand(4);
        }
        if(event->key()==Qt::Key_5)
        {
           control.sendCommand(5);
        }
        if (event->key() == Qt::Key_6)
        {
            control.sendCommand(6);
        }
        if (event->key() == Qt::Key_7)
        {
            control.sendCommand(7);
        }
        if (event->key() == Qt::Key_8)
        {
            control.sendCommand(8);
        }
    }
private:
    ControlFly control;
};
int main(int args,char** argv)
{
    QApplication app(args, argv);
    Test t;
    t.show();
    return app.exec();
}
