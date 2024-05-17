#include "bassvep.h"

BASSVEP::BASSVEP(QObject *parent) : QObject(parent)
{
    CustomMessageHandler::installMessageHandler();
    initCCA();
    initBCIMonitor();
    initFilter();
    initControlFly();
    initSSVEPWidget();
    initTaskWidget();
    initIndexWidget();
    connect(bcimonitor,&BCIMonitor::markChanged,cca,&CCA::start);
    connect(bcimonitor,&BCIMonitor::filterData,this,[=](QList<double> data){
        data=filter->filter(data);
        cca->append(data);
    });
    connect(cca,&CCA::result,controlfly,&ControlFly::command);

    connect(taskwidget,&start_game::start,this,[=](){
        ssvep_widget->start();
        bcimonitor->startDataTransmit();
    });
    indexwidget->show();
}

BASSVEP::~BASSVEP()
{
    delete bcimonitor;
    delete cca;
    delete filter;
    delete controlfly;
    delete ssvep_widget;
}

void BASSVEP::initFilter()
{
    filter=new DataProcess::Filter;
    filter->init(32,1000,1,15);
}

void BASSVEP::initBCIMonitor()
{
    bcimonitor=new BCIMonitor;
    bcimonitor->setFileMsg("lx",123);
}

void BASSVEP::initControlFly()
{
    controlfly=new ControlFly;
}

void BASSVEP::initSSVEPWidget()
{
    ssvep_widget=new SSVEPWidget;
}

void BASSVEP::initIndexWidget()
{
    indexwidget=new IndexWidget;
    indexwidget->addWidget("采集",bcimonitor);
    indexwidget->addWidget("任务",taskwidget);
    //    indexwidget->addWidget("任务");
}

void BASSVEP::initTaskWidget()
{
    taskwidget=new start_game;
}
void BASSVEP::initCCA()
{
    cca=new CCA;
}
