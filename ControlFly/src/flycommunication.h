#ifndef FLYCOMMUNICATION_H
#define FLYCOMMUNICATION_H

#include <QObject>
#include "QUdpSocket"
#include "h264decoder.hpp"
#include "QImage"
#include "videocommunication.h"
#include "commandcommunication.h"
class FlyCommunication : public QObject
{
    Q_OBJECT
public:
    explicit FlyCommunication(QObject *parent = nullptr);
    ~FlyCommunication();
    void sendCommand(int);
    void initCommunication();
signals:
    void receiveFrameFinished(QImage);
    void currentCommand(QString);
    void batteryChanged(quint8);
private slots:
private:
    //指令socket
    CommandCommunication *command_communication;
    VideoCommunication *video_communication;
};

#endif // FLYCOMMUNICATION_H
