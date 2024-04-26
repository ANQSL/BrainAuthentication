#include "brainhearteye.h"
#include "QApplication"
#include "testwidget.h"
int main(int args,char** argv)
{
    QApplication app(args,argv);
    testWidget w;
    w.show();
    return  app.exec();
}
