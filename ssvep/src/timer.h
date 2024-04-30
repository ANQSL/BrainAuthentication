#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include "QThread"
class Timer:public QThread
{
    Q_OBJECT
public:
    Timer(QObject *parent=nullptr);
    void start(quint64 msec);
    void stop();
    void run() override;
signals:
    void timeout();
private:
    unsigned long msec;
    bool status;
};

#endif // TIMER_H
