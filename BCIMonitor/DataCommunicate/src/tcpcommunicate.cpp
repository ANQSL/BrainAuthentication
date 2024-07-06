#include "tcpcommunicate.h"
#include "QTcpSocket"
TcpCommunicate::TcpCommunicate(QObject *parent) : QObject(parent)
{
    model=false;
    init();
}

TcpCommunicate::~TcpCommunicate()
{
    stop();
    if(model)
    {
       delete  server;
    }
    delete  mark_server;
}

void TcpCommunicate::start()
{
    //开启数据服务
    if(model)
    {
        server->listen(QHostAddress::Any,7777);
    }
    else
    {
        socket->connectToHost("127.0.0.1",7777);
        socket->waitForConnected();
    }
}

void TcpCommunicate::stop()
{    
    if(model)
    {
        server->close();
        if(socket==NULL)
        {
            delete socket;
        }
    }
    else
    {
        socket->disconnect();
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
    if(model)
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
    else
    {
        socket=new QTcpSocket;
        setSocketConnect();
    }
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
    //开始mark服务
    mark_server->listen(QHostAddress::Any,8888);

}

void TcpCommunicate::setSocketConnect()
{
//    connect(socket,&QTcpSocket::disconnected,this,[=](){
//       delete socket;
//       socket=NULL;
//    });
    connect(socket,&QTcpSocket::readyRead,this,[=](){
       QByteArray data=socket->readAll();
       socket->disconnectFromHost();
//       qDebug()<<QString(data);
       emit result(data);
    });
}
void TcpCommunicate::setMarkSocketConnect()
{
    connect(mark_socket,&QTcpSocket::readyRead,this,[=](){
       QByteArray data=mark_socket->readAll();
       for(int i=0;i<data.size();i++)
       {
           quint8 result_value=data[i];
           emit readMark(result_value);
       }

    });
}
