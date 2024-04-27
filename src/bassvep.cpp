#include "bassvep.h"

BASSVEP::BASSVEP(QObject *parent) : QObject(parent)
{
    initSSVEP();
    initBCIMonitor();
    connect(ssvep,&SSVEP::markChanged,bcimonitor,&BCIMonitor::appendMark);
    ssvep->show();
    bcimonitor->show();
}

void BASSVEP::initBCIMonitor()
{
    bcimonitor=new BCIMonitor;
}

void BASSVEP::initSSVEP()
{
    ssvep=new SSVEP;
}
