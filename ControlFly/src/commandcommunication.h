#ifndef COMMANDCOMMUNICATION_H
#define COMMANDCOMMUNICATION_H

#include <QObject>
#include "QUdpSocket"
class CommandCommunication : public QObject
{
    Q_OBJECT
public:
    explicit CommandCommunication(QObject *parent = nullptr);
    ~CommandCommunication();
    //开启视频流
    void streamon();
    //关闭视频流
    void streamoff();
    //起飞
    void takeoff();
    //降落
    void land();
    //悬停
    void hover();
    //前进
    void forward();
    //后退
    void back();
    //左移
    void left();
    //右移
    void right();
    //上升
    void up();
    //下降
    void down();
    //电量查询
    quint8 getBattery();
    //指令发送
    void sendCommand(QByteArray);
     void sendCommand(int);
signals:
    void currentCommand(QString);
    void batteryChanged(quint8);
private:
    QUdpSocket *socket;
    QHostAddress IP;
    quint16 port;
    //当前是否是起飞状态
    bool running_status;
    //上次命令执行过去几秒
    quint8 command_continue_time;
    QTimer *timer;
    //当前执行指令
    QString command;
    //当前电量
    uint8_t current_battery;
};

#endif // COMMANDCOMMUNICATION_H
