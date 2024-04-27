#ifndef BASSVEP_H
#define BASSVEP_H

#include <QObject>
#include "ssvep.h"
#include "bcimonitor.h"
class BASSVEP : public QObject
{
    Q_OBJECT
public:
    explicit BASSVEP(QObject *parent = nullptr);

signals:
private:
    SSVEP *ssvep;
    void initSSVEP();
    BCIMonitor *bcimonitor;
    void initBCIMonitor();
};

#endif // BASSVEP_H
