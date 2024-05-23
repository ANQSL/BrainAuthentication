#ifndef BASSVEP_H
#define BASSVEP_H

#include <QObject>
#include "cca.h"
#include "bcimonitor.h"
#include "dataprocess.h"
#include "controlfly.h"
#include "ssvepwidget.h"
#include "custommessagehandler.h"
#include "indexwidget.h"
#include "start_game.h"
#include "calculatetest.h"
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
    void initControlFly();
    //ssvepwidget
    SSVEPWidget *ssvep_widget;
    void initSSVEPWidget();

    //主页
    IndexWidget *indexwidget;
    void initIndexWidget();
    //任务
    start_game  *taskwidget;
    void initTaskWidget();


    //算法验证
    CalculateTest calculate_test;


};

#endif // BASSVEP_H
