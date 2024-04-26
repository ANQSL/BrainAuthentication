#ifndef FILEAMPLIFIER_H
#define FILEAMPLIFIER_H

#include <QObject>
#include <QWidget>
#include "amplifierdevice.h"
#include "connectwidget.h"
#include "eegdata.h"
class FIleAmplifier : public AmplifierDevice
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FileAmplifier" FILE "fileamplifier.json")
    Q_INTERFACES(AmplifierDevice)
public:
    explicit FIleAmplifier();
    void start() override;
    void stop() override;
    QStringList getChannelName() override;
    quint8 getChannnelNum() override;
    quint16 getSampleRate() override;
    QWidget * getConfigWidget() override;
    QWidget * getConnectWidget() override;
    QList<double> getOneData() override;
    QList<QList<double> > getArrayData() override;
    QList<uint8_t> getEEGGameIndex();//获取游戏的脑电索引
    QList<uint8_t> getEEGIndex(); //获取全部脑电的索引
    QList<uint8_t> getMuscleIndex();  //获取肌电的索引
    QList<uint8_t> getBreathIndex();  //获取呼吸的索引
    QList<uint8_t> getHeartIndex();  //获取心电的索引
    bool connectStatus() override;
signals:
private:
    void readData(QString);
    ConnectWidget *connectwidget;
    void initConnectWidget();
    void closeDevice();
    quint8  channel_num;
    QStringList channel_labels;
    quint16 srate;
    EEGData eegdata;

    //文件的状态
    bool status;
    //数据获取状态；
    bool data_status;

};

#endif // FILEAMPLIFIER_H
