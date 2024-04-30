#include "bassvep.h"

BASSVEP::BASSVEP(QObject *parent) : QObject(parent)
{
    initCCA();
    initBCIMonitor();
    connect(bcimonitor,&BCIMonitor::markChanged,cca,&CCA::start);
    connect(bcimonitor,&BCIMonitor::filterData,cca,&CCA::append);
    bcimonitor->show();
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
