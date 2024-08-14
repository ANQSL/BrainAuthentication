#include "controlfly.h"

ControlFly::ControlFly(QObject *parent) : QObject(parent)
{
    communication=new FlyCommunication;
    control_widget=new FlyControlWidget;
    connect(communication,&FlyCommunication::receiveFrameFinished,control_widget,&FlyControlWidget::setVideoFrame);
    connect(communication,&FlyCommunication::currentCommand,control_widget,&FlyControlWidget::setCurrentCommand);
    connect(communication, &FlyCommunication::batteryChanged, control_widget, &FlyControlWidget::setBttery);
    communication->initCommunication();
}
ControlFly::~ControlFly()
{
    delete control_widget;
    delete communication;
}

void ControlFly::sendCommand(int command)
{
    communication->sendCommand(command);
}

void ControlFly::startControl()
{
    control_widget->startControl();
}

void ControlFly::showControlWidget()
{
    control_widget->show();
}
