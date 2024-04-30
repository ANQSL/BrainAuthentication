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
    void readMark(quint8);
private:
    //数据端口
    QTcpServer *server;
    QTcpSocket *socket=NULL;
    void init();
    void setSocketConnect();
    //标签端口
    QTcpServer *mark_server;
    QTcpSocket *mark_socket=NULL;
    void setMarkSocketConnect();



};

#endif // TCPSEND_H
