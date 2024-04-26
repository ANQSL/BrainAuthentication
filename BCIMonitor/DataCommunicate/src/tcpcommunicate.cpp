#include "tcpcommunicate.h"
#include "QTcpSocket"
TcpCommunicate::TcpCommunicate(QObject *parent) : QObject(parent)
{
    init();
}

TcpCommunicate::~TcpCommunicate()
{
    stop();
    delete  server;
}

void TcpCommunicate::start()
{
    server->listen(QHostAddress::Any,7777);
}

void TcpCommunicate::stop()
{    
    server->close();
    if(socket==NULL)
    {
        delete socket;
    }
}
void TcpCommunicate::send(double *data,quint16 data_len)
{
    if(socket!=NULL)
    {
        socket->write((char*)data,sizeof (double)*data_len);
    }
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
