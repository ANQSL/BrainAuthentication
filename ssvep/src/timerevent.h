#ifndef TIMEREVENT_H
#define TIMEREVENT_H

#include "QEvent"
class TimerEvent:public QEvent
{
public:
    static const QEvent::Type EventType;
    TimerEvent();
};

#endif // TIMEREVENT_H
