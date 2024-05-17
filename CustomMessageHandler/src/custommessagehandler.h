#ifndef CUSTOMMESSAGEHANDLER_H
#define CUSTOMMESSAGEHANDLER_H

#include <QObject>
class Message:public QObject
{
    Q_OBJECT
public:
    void rececive(QtMsgType,QString);
signals:
    void readyRead(QtMsgType,QString msg);
};
class CustomMessageHandler : public QObject
{
    Q_OBJECT
public:
    //处理
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    //重定向QDebug
    static Message* installMessageHandler();
signals:
private:
    static Message *message;
};

#endif // CUSTOMMESSAGEHANDLER_H
