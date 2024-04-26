#ifndef SELFAMPLIFIER_H
#define SELFAMPLIFIER_H

#include <QObject>
#include "amplifierdevice.h"
#include "dataanalysis.h"
#include "encode.h"
#include "eegdata.h"
#include "QtSerialPort/QSerialPort"
#include "connectwidget.h"
#include "QMap"
class SelfAmplifier : public AmplifierDevice
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "SelfAmplifier" FILE "selfamplifier.json")
    Q_INTERFACES(AmplifierDevice)
public:
    explicit SelfAmplifier();
    ~SelfAmplifier();
    void start() override;
    void stop() override;
    QStringList getChannelName() override;
    quint8 getChannnelNum() override;
    quint16 getSampleRate() override;
    QWidget * getConfigWidget() override;
    QWidget * getConnectWidget() override;
    QList<double> getOneData() override;
    QList<QList<double> > getArrayData() override;
    QList<uint8_t> getEEGGameIndex() override;
    QList<uint8_t> getEEGIndex() override;
    QList<uint8_t> getMuscleIndex() override;
    QList<uint8_t> getBreathIndex() override;
    QList<uint8_t> getHeartIndex() override;
    bool connectStatus() override;

private slots:
    void ConnectDevice(QMap<QString,QVariant>);
    void serialErrorDeal(QSerialPort::SerialPortError);
    void setPort(QString name);
    void setBaudRate(quint32 band_rate);
    void append(QList<double>);
private:
    typedef  struct device_param
    {
        QString serial_name;
        qint32  baud_rate;
        QSerialPort::StopBits   stop_bit;
        QSerialPort::DataBits   data_bit;
        QSerialPort::Parity    parity_bit;
        QSerialPort::FlowControl  flow_control;
    }DeviceParam;
    //设备连接参数
    DeviceParam device_param;
    void initDeivceParam();
    //数据串口
    QSerialPort *serial_data;
    bool data_status;//数据获取状态
    void  initSerialData();
    void setSerialDataConnect();
    //解析线程
    DataAnalysis *data_analysis;
    void initAnalysis();
    void setAnalysisConnect();
    //数据
    EEGData *eegdata;
    //导联状态：
    QList<bool> off_indicate;
    //连接窗口
    ConnectWidget *connectwidget;
    void initConnetWidget();
    void setConnectConnect();

    void init();
    void setConnect();

};

#endif // SELFAMPLIFIER_H
