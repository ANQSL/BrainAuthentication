#ifndef TCPSEND_H
#define TCPSEND_H

#include <QObject>
#include "QTcpServer"
class TcpCommunicate : public QObject
{
    Q_OBJECT
public:
    explicit TcpCommunicate(QObject *parent = nullptr);
    ~TcpCommunicate();
    void start();
    void stop();
    void send(double *data,quint16 data_len);
signals:
    void result(quint8);
    void commandSignal(quint8);
private:
    QTcpServer *server;
    QTcpSocket *socket=NULL;

    QTcpServer *command_server=NULL;
    QTcpSocket *command_socket=NULL;

    void initCommand();
    void setCommandConnect();
    void init();
    void setSocketConnect();


};

#endif // TCPSEND_H
