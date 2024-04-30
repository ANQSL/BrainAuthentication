#include "bassvep.h"
#include "QApplication"
int main(int args,char **argv)
{
    QApplication app(args,argv);
    BASSVEP bassvep;
    return app.exec();
}
