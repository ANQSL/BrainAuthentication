#include "communication.h"
#include "QDebug"
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
        qDebug()<<mark_socket->waitForConnected(10);
    }

}
