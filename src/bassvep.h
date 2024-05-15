#ifndef BASSVEP_H
#define BASSVEP_H

#include <QObject>
#include "cca.h"
#include "bcimonitor.h"
#include "dataprocess.h"
#include "controlfly.h"
class BASSVEP : public QObject
{
    Q_OBJECT
public:
    explicit BASSVEP(QObject *parent = nullptr);
    ~BASSVEP();
signals:
private:
    //滤波器
    DataProcess::Filter *filter;
    void initFilter();
    //cca算法
    CCA *cca;
    void initCCA();
    //采集器
    BCIMonitor *bcimonitor;
    void initBCIMonitor();
    //控制
    ControlFly *controlfly;


};

#endif // BASSVEP_H
