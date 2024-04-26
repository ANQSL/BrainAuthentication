#ifndef AMPLIFIERDEVICE_H
#define AMPLIFIERDEVICE_H

#include <QtPlugin>
class AmplifierDevice:public QObject
{
    Q_OBJECT
public:
    virtual ~AmplifierDevice(){};
    virtual void start()=0;//开始采集
    virtual void stop()=0;//停止采集
    virtual QStringList getChannelName()=0;//获取通道标签
    virtual quint8 getChannnelNum()=0; //获取通道数目
    virtual quint16 getSampleRate()=0; //获取采样率
    virtual QWidget* getConnectWidget()=0;//获取设备连接窗口
    virtual QWidget* getConfigWidget()=0;//获取配置窗口
    virtual QList<double> getOneData()=0;//获取一帧数据
    virtual QList<QList<double>> getArrayData()=0;//获取一组数据
    virtual QList<uint8_t> getEEGGameIndex()=0;//获取游戏的脑电索引
    virtual QList<uint8_t> getEEGIndex()=0; //获取全部脑电的索引
    virtual QList<uint8_t> getMuscleIndex()=0;  //获取肌电的索引
    virtual QList<uint8_t> getBreathIndex()=0;  //获取呼吸的索引
    virtual QList<uint8_t> getHeartIndex()=0;  //获取心电的索引
    virtual bool connectStatus()=0;
};
Q_DECLARE_INTERFACE(AmplifierDevice, "AmplifierDevice")
#endif // AMPLIFIERDEVICE_H
