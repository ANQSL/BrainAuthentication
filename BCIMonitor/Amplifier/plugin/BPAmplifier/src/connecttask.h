#ifndef CONNECTTask_H
#define CONNECTTask_H

#include <QObject>
#include "SDK.h"
#include "QThread"
class ConnectTask : public QObject
{
    Q_OBJECT
public:
    explicit ConnectTask(QObject *parent = nullptr);
    void setAmplifier(CAmplifier *);
    void SearchDeviceNum(int family, int type);
    void connectDevice(int);
    void connectStatus();
signals:
    void searchFinished(int);
    void connectResult(bool);
    void status(bool);
private:
    CAmplifier *amplifier;
};

#endif // CONNECTTask_H
