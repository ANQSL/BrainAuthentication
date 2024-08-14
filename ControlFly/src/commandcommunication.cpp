#include "commandcommunication.h"
#include "QTimer"
#include "QEventLoop"
CommandCommunication::CommandCommunication(QObject *parent) : QObject(parent)
{
    socket=new QUdpSocket;
    IP.setAddress("192.168.1.11");
    port=8889;
    command_continue_time=0;
    running_status=false;
    socket->bind(QHostAddress::Any,port);
    timer=new QTimer();
    connect(timer,&QTimer::timeout,this,[=](){
        command_continue_time++;
        if(command_continue_time==10)
        {
            hover();
        }
        getBattery();

    });
}

CommandCommunication::~CommandCommunication()
{
    delete socket;
    delete timer;
}
void CommandCommunication::streamon()
{
    sendCommand("streamon");
    //sendCommand("setfps high");
    //sendCommand("setresolution high");
}

void CommandCommunication::streamoff()
{
    sendCommand("streamoff");
}
void CommandCommunication::takeoff()
{
    if(!running_status)
    {
        sendCommand("takeoff");
        running_status=true;
        timer->start(1000);
        emit currentCommand("起飞");
    }

}
void CommandCommunication::land()
{
    if(running_status)
    {
      sendCommand("land");
      running_status=false;
      timer->stop();
      emit currentCommand("降落");
    }

}

void CommandCommunication::hover()
{
    if(running_status)
    {
        sendCommand("stop");
        emit currentCommand("悬停");
    }
}

void CommandCommunication::forward()
{
    if(running_status)
    {
        sendCommand("forward 50");
        emit currentCommand("前进");
    }
}

void CommandCommunication::back()
{
    if(running_status)
    {
        sendCommand("back 50");
        emit currentCommand("后退");
    }
}

void CommandCommunication::left()
{
    if(running_status)
    {
        sendCommand("left 100");
        emit currentCommand("左移");
    }
}

void CommandCommunication::right()
{
    if(running_status)
    {
        sendCommand("right 100");
        emit currentCommand("右移");
    }
}
void CommandCommunication::up()
{
    if (running_status)
    {
        sendCommand("up 100");
        emit currentCommand("上升");
    }
}
void CommandCommunication::down()
{
    if (running_status)
    {
        sendCommand("down 50");
        emit currentCommand("下降");
    }
}
quint8 CommandCommunication::getBattery()
{
    sendCommand("battery?");
    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray buffer;
    socket->readDatagram((char*)buffer.data(), 1024, &IP, &port);
    uint8_t battery = buffer.toUInt();
    if (battery != 0)
    {
        this->current_battery = battery;
        emit batteryChanged(battery);
    }
    return current_battery;
}
void CommandCommunication::sendCommand(QByteArray command)
{
    if (command != "battery?")
    {
        command_continue_time=0;
    }
    this->command = command;
    socket->writeDatagram(command,IP,port);
}
void CommandCommunication::sendCommand(int command_id)
{
    switch (command_id) {
        case 0:
            hover();
        break;
        case 1:
            takeoff();
        break;
        case 2:
            land();
        break;
        case 3:
            forward();
        break;
        case 4:
            back();
        break;
        case 5:
            left();
        break;
        case 6:
            right();
        break;
  /*      case 7:
            up();
            break;
        case 8:
            down();
            break;*/
    }
}
