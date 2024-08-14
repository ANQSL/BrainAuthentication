#include "flycommunication.h"
#include "libavcodec/avcodec.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include "QImage"
FlyCommunication::FlyCommunication(QObject *parent) : QObject(parent)
{
    command_communication=new CommandCommunication;
    video_communication=new VideoCommunication;
    connect(command_communication,&CommandCommunication::currentCommand,this,&FlyCommunication::currentCommand);
    connect(command_communication, &CommandCommunication::batteryChanged, this, &FlyCommunication::batteryChanged);
    connect(video_communication,&VideoCommunication::receiveFrameFinished,this,&FlyCommunication::receiveFrameFinished);

}

FlyCommunication::~FlyCommunication()
{
    delete command_communication;
    delete video_communication;
}
void FlyCommunication::sendCommand(int command_id)
{
    command_communication->sendCommand(command_id);
}

void FlyCommunication::initCommunication()
{
    command_communication->sendCommand("command");
    command_communication->streamon();
    video_communication->start();
    //command_communication->getBattery();
}

