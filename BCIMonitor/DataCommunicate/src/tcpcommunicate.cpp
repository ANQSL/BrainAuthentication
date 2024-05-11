#include "tcpcommunicate.h"
#include "QTcpSocket"
TcpCommunicate::TcpCommunicate(QObject *parent) : QObject(parent)
{
    init();
    initCommand();
}

TcpCommunicate::~TcpCommunicate()
{
    stop();
    delete  server;
}

void TcpCommunicate::start()
{
    server->listen(QHostAddress::Any,7777);
    command_server->listen(QHostAddress::Any,8888);
}

void TcpCommunicate::stop()
{    
    server->close();
    command_server->close();
}
void TcpCommunicate::send(double *data,quint16 data_len)
{
    if(socket!=NULL)
    {
        socket->write((char*)data,sizeof (double)*data_len);
    }
}
void TcpCommunicate::initCommand()
{
    command_server=new QTcpServer;
    connect(command_server,&QTcpServer::newConnection,this,[=](){
        qDebug()<<"新连接";
        if(command_server->hasPendingConnections())
        {
            command_socket=command_server->nextPendingConnection();
            setCommandConnect();

        }
    });
}
void TcpCommunicate::setCommandConnect()
{
    connect(command_socket,&QTcpSocket::readyRead,this,[=](){
       QByteArray data=command_socket->readAll();
       quint8 result_value=data.toInt();
       emit commandSignal(result_value);

    });
}
void TcpCommunicate::init()
{
    server=new QTcpServer;
    connect(server,&QTcpServer::newConnection,this,[=](){
        qDebug()<<"新连接";
        if(server->hasPendingConnections())
        {
            socket=server->nextPendingConnection();
            setSocketConnect();
        }
    });

}

void TcpCommunicate::setSocketConnect()
{
//    connect(socket,&QTcpSocket::disconnected,this,[=](){
//       delete socket;
//       socket=NULL;
//    });
    connect(socket,&QTcpSocket::readyRead,this,[=](){
       QByteArray data=socket->readAll();
       quint8 result_value=data.toInt();
//       qDebug()<<data;
       emit result(result_value);

    });
}
