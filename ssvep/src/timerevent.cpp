#include "timerevent.h"
const QEvent::Type TimerEvent::EventType = static_cast<QEvent::Type>(QEvent::registerEventType());
TimerEvent::TimerEvent():QEvent(EventType)
{

}
