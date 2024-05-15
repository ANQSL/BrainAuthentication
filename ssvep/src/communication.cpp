#include "communication.h"
#include "iostream"
Communication::Communication(QObject *parent) : QObject(parent)
{
    mark_socket=new QTcpSocket();

}

Communication::~Communication()
{
    delete  mark_socket;
}

void Communication::append(quint8 mark)
{
    char mark_value=mark;
    mark_socket->write(&mark_value,1);
}

void Communication::connectAmplifier()
{
    if(mark_socket->state()!=QAbstractSocket::ConnectedState)
    {
        mark_socket->connectToHost("127.0.0.1",8888);
        bool isok=mark_socket->waitForConnected(10);
        if(isok)
        {
            std::cout<<"连接成功"<<std::endl;
        }
        else
        {
            std::cout<<"连接失败"<<std::endl;
        }
        std::cout.flush();
    }

}
