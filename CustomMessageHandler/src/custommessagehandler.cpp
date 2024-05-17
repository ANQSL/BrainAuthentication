#include "custommessagehandler.h"
#include "iostream"
#include "Windows.h"
#include "QTextStream"
#include "QDebug"
Message* CustomMessageHandler::message=NULL;
void CustomMessageHandler::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(!msg.contains("MsgType"))
    {
        QTextStream console(stdout);
        console<<msg<<endl;
    }
    else
    {
        CustomMessageHandler::message->rececive(type,msg);
    }
}

Message* CustomMessageHandler::installMessageHandler()
{
    CustomMessageHandler::message=new Message;
    qInstallMessageHandler(messageHandler);
    return CustomMessageHandler::message;
}

void Message::rececive(QtMsgType type, QString msg)
{
    QTextStream console(stdout);
    console<<msg<<endl;
    emit readyRead(type,msg);
}
