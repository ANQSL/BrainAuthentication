#include "QCoreApplication"
#include "custommessagehandler.h"
#include "QDebug"
int main(int args,char* *argv)
{
    QCoreApplication app(args,argv);
    CustomMessageHandler::installMessageHandler();
    qDebug()<<"123";
    qDebug()<<"MsgType=123,data=123123";
    return app.exec();
}
