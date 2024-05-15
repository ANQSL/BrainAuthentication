#include "bassvep.h"

BASSVEP::BASSVEP(QObject *parent) : QObject(parent)
{
    initCCA();
    initBCIMonitor();
    connect(bcimonitor,&BCIMonitor::markChanged,cca,&CCA::start);
    connect(bcimonitor,&BCIMonitor::filterData,this,[=](QList<double> data){
        data=filter->filter(data);
        cca->append(data);
    });
    connect(cca,&CCA::result,controlfly,&ControlFly::command);
            bcimonitor->show();
}

BASSVEP::~BASSVEP()
{
    delete bcimonitor;
    delete cca;
    delete filter;
    delete controlfly;
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
void BASSVEP::initCCA()
{
    cca=new CCA;
}
