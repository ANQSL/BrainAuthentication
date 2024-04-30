#ifndef BASSVEP_H
#define BASSVEP_H

#include <QObject>
#include "cca.h"
#include "bcimonitor.h"
class BASSVEP : public QObject
{
    Q_OBJECT
public:
    explicit BASSVEP(QObject *parent = nullptr);

signals:
private:
    CCA *cca;
    void initCCA();
    BCIMonitor *bcimonitor;
    void initBCIMonitor();
};

#endif // BASSVEP_H
