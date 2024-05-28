#ifndef DATATHREAD_H
#define DATATHREAD_H

#include <QThread>
#include "amplifierdevice.h"
#include "filter.h"
class DataThread : public QThread
{
    Q_OBJECT
public:
    explicit DataThread(QObject *parent = nullptr);
    void run() override;
    void setDeivce(AmplifierDevice *);
    void setStatus(bool value);
    void destroy();
    bool getStatus() const;
    void clearFilter();
signals:
    void readFinish(QList<double>);
    void rawDataFinished(QList<double>);
    void readDataFinished(QList<double>,QList<double>);
private:
    bool status;
    bool destroyFlag;
    AmplifierDevice *device;
    Filter filter;
};

#endif // DATATHREAD_H
