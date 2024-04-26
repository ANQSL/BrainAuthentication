#ifndef BPAMPLIFIER_H
#define BPAMPLIFIER_H
#include "QObject"
#include "QtPlugin"
#include "amplifierdevice.h"
#include "SDK.h"
#include "RawDataHandlerExample.h"
#include "connectdialog.h"
#include "connecttask.h"
class  BPAmplifier: public AmplifierDevice
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "AmplifierDevice" FILE "bpamplifier.json")
    Q_INTERFACES(AmplifierDevice)
public:
    BPAmplifier();
    ~BPAmplifier();
    void start() override;
    void stop() override;
    QStringList getChannelName() override;
    quint8 getChannnelNum() override;
    quint16 getSampleRate() override;
    QWidget * getConfigWidget() override;
    QWidget * getConnectWidget() override;
    QList<double> getOneData() override;
    QList<QList<double> > getArrayData() override;
    bool connectStatus() override;

    QList<uint8_t> getEEGGameIndex() override;

    QList<uint8_t> getEEGIndex() override;
//    QList<uint8_t> getOtherIndex() override;
    QList<uint8_t> getBreathIndex() override;
    QList<uint8_t> getMuscleIndex() override;
    QList<uint8_t> getHeartIndex() override;


signals:
    void searchSignal(int,int);
    void connectSignal(int);
    void statusSignal();
private slots:
    void reviceSearchResult(int);
    void receiveConnectResult(bool);
    void receviceStatus(bool);
private:
    void init();
    CAmplifier amplifier;
    RawDataHandler *rdh;
    void initRdh();
    void deleteRdh();
    QWidget *configWidget;
    void deleteConfigWidget();
    //系列
    int family;
    //接口类型
    int type;
    //设备状态
    QTimer *connect_check_task;
    void initCheckTask();
    bool status=false;
    //连接窗口
    ConnectDialog *connectWidget;
    //初始化连接窗口
    void initConnectWidget();
    void deleteConnectWidget();

    //选择设备型号
    void setDeviceFamily(int);
    void setInterFaceType(int);
    //搜索输入接口的设备数目
    void SearchDeviceNum();
    //设备连接
    void ConnectDevice(int);

    ConnectTask *connect_task;
    QThread *connect_thread;
    void initConnectThread();
    void deleteConnecteThread();

};

#endif // BPAMPLIFIER_H
