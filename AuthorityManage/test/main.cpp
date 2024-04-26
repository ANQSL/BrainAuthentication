#include "QApplication"
#include "authoritymanage.h"
#include "managewidget.h"
int main(int args,char **argv)
{
    QApplication app(args,argv);
    AuthorityManage am;
    return app.exec();
}
