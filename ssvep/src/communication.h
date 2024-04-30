#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include "QTcpSocket"
class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = nullptr);
    ~Communication();
    void append(quint8);
    void connectAmplifier();
signals:
private:
    QTcpSocket *mark_socket;
};

#endif // COMMUNICATION_H
