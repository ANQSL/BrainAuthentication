#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "flycommunication.h"
#include "flycontrolwidget.h"
class ControlFly : public QObject
{
    Q_OBJECT
public:
    explicit ControlFly(QObject *parent = nullptr);
    ~ControlFly();
    void sendCommand(int);
    void startControl();
    void showControlWidget();
signals:
private:
    FlyCommunication *communication;
    FlyControlWidget *control_widget;
};

#endif // CONTROL_H
