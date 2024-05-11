#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include "QPluginLoader"
#include "amplifierdevice.h"
#include "QTimer"
#include "datathread.h"
#include "pluginmanage.h"
#include "pluginwidget.h"
class  Amplifier:public QObject
{
    Q_OBJECT
public:
    Amplifier();   
    ~Amplifier();
    void start();
    void pause();
    void stop();
    QStringList getChannelName();//获取通道数目
    QVariantList getChanlocs(); //获取导联信息
    QWidget* getConnectWidget();//获取设备连接窗口
    QWidget* getConfigWidget();//获取配置窗口
    QList<double> getOneData();//获取一帧数据
    quint16 getSampleRate();
    QList<uint8_t> getEEGGameIndex();//获取12个EEG通道的索引
    QList<uint8_t> getEEGIndex(); //获取全部脑电的索引
    QList<uint8_t> getMuscleIndex(); //获取肌电的索引
    QList<uint8_t> getBreathIndex(); //获取呼吸的索引
    QList<uint8_t> getHeartIndex(); //获取心电的索引
    void showConnectWidget();
    PluginWidget *getPluginWidget() const;
    void showPluginWidget();
    void setDecodeStatus(bool);
    void clearFilter();
    bool checkStatus();//检查放大器是否加载
private slots:
    void loadPluginStatus(bool);

signals:
    void disconnected();
    void readyRead(QList<double>);
    void rawDataFinished(QList<double>);
    void error(QString);
    void connected();
    void loadPluginSucceed();

private slots:
    void checkConnectStatus();
private:
    AmplifierDevice* amplifierdevice=NULL;
    //定时器
    QTimer *timer;
    void  initTimer();
    //数据线程
    DataThread *datathread;
    void initDataThread();

    //插件管理
    PluginManage *pluginmanage;
    void initPluginManage();
    //插件管理页面
    PluginWidget *pluginwidget;
    void  initPluginWidget();

    //连接标志
    bool connect_status=false;
};

#endif // AMPLIFIER_H
