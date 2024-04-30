#include "timer.h"
#include "QDateTime"
#include "iostream"
#include "QDebug"
#include "QCoreApplication"
#include "timerevent.h"
Timer::Timer(QObject *parent):QThread(parent)
{

}

void Timer::start(quint64 msec)
{
    this->msec=msec;
    status=true;
    QThread::start();
}

void Timer::stop()
{
    status=false;
}
void Timer::run()
{
    auto start_time=std::chrono::high_resolution_clock::now();
    while (status) {
         auto end_time=std::chrono::high_resolution_clock::now();
         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
         unsigned long time_cost= duration.count();
         if(time_cost>=(16666))
         {
             emit timeout();
             start_time=end_time;
         }
    }
}
