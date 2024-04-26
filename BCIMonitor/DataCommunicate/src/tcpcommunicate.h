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
private:
    QTcpServer *server;
    QTcpSocket *socket=NULL;
    void init();
    void setSocketConnect();


};

#endif // TCPSEND_H
