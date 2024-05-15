#include "controlfly.h"

ControlFly::ControlFly(QObject *parent) : QObject(parent)
{
    server=new QTcpServer;
    server->listen(QHostAddress::Any,6666);
    setConnect();
}

ControlFly::~ControlFly()
{
    delete server;
}

void ControlFly::command(quint8 index)
{
    if(socket!=NULL)
    {
        char data=index+48;
        socket->write(&data,1);
    }
}

bool ControlFly::connectStatus()
{
    if(socket)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void ControlFly::setConnect()
{
    connect(server,&QTcpServer::newConnection,this,[=](){
       if(server->hasPendingConnections())
       {
           qDebug()<<"游戏端已连接";
           socket=server->nextPendingConnection();
           setSocketConnect();
       }
    });
}

void ControlFly::setSocketConnect()
{
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketDeal(QAbstractSocket::SocketError)));
}

void ControlFly::socketDeal(QAbstractSocket::SocketError socketError)
{
    socket=NULL;
    qDebug()<<socketError;
}

