#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "QTcpServer"
#include "QTcpSocket"
#include "QProcess"
class ControlFly : public QObject
{
    Q_OBJECT
public:
    explicit ControlFly(QObject *parent = nullptr);
    ~ControlFly();
    void command(quint8);
    bool connectStatus();
signals:
private:
    QTcpServer *server;
    QTcpSocket *socket=NULL;
    void setConnect();
    void setSocketConnect();
    //任务进程
    QProcess *task_process;
    void initTaskProcess();
private slots:
    void socketDeal(QAbstractSocket::SocketError socketError);
};

#endif // CONTROL_H
