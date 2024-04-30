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
    delete  mark_server;
}

void TcpCommunicate::start()
{
    server->listen(QHostAddress::Any,7777);
    mark_server->listen(QHostAddress::Any,8888);
}

void TcpCommunicate::stop()
{    
    server->close();
    if(socket==NULL)
    {
        delete socket;
    }
    mark_server->close();
    if(socket==NULL)
    {
        delete mark_socket;
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

    //标签端口
    mark_server=new QTcpServer;
    connect(mark_server,&QTcpServer::newConnection,this,[=](){

        if(mark_server->hasPendingConnections())
        {
             qDebug()<<"标签新连接";
             mark_socket=mark_server->nextPendingConnection();
             setMarkSocketConnect();
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
       emit result(result_value);

    });
}

void TcpCommunicate::setMarkSocketConnect()
{
    connect(mark_socket,&QTcpSocket::readyRead,this,[=](){
       QByteArray data=mark_socket->readAll();
       for(int i=0;i<data.size();i++)
       {
           quint8 result_value=data[i];
//           qDebug()<<result_value;
           emit readMark(result_value);
       }

    });
}
