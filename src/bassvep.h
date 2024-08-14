#ifndef BASSVEP_H
#define BASSVEP_H

#include <QObject>
#include "bcimonitor.h"
#include "dataprocess.h"
#include "controlfly.h"
#include "ssvepwidget.h"
#include "custommessagehandler.h"
#include "indexwidget.h"
#include "start_game.h"
#include "calculatetest.h"
#include "authoritymanage.h"
#include "biteteethrecognition.h"
#include "brainrecognition.h"
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
    //权限管理
    AuthorityManage authority_manage;
    //算法验证
    CalculateTest calculate_test;
    //用户
    User user;
    //登录次数
    quint8 login_time=0;
    //咬牙算法
    Calculate::BiteTeethRecognition bite_teeth_recognition;
    //脑纹识别算法
    Calculate::DeepLearn::BrainRecognition brain_recognition;
    //登录状态
    bool login_status=false;
};

#endif // BASSVEP_H
