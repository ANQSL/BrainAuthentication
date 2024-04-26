#include "ssvep.h"
#include "QApplication"
int main(int args,char **argv)
{
    QApplication app(args,argv);
    SSVEP ssvep;
    ssvep.show();
    return app.exec();
}
