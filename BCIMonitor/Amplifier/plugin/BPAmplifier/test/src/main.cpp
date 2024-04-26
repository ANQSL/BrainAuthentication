#include "testwidget.h"
#include "QApplication"
int main(int args,char** argv)
{
    QApplication app(args,argv);
    TestWidget w;
    w.show();
    return app.exec();
}
