#ifndef AMPLIFER_H
#define AMPLIFER_H

#include <QObject>
#include "QSerialPort"
#include "QMap"
#include "QVariant"
class DataAnalysis;
class Encode;
class EEGData;
class ConnectWidget;
class Amplifer : public QObject
{
    Q_OBJECT
public:
    explicit Amplifer();
    ~Amplifer();
    void setPort(QString name);
    bool setBaudRate(quint32 band_rate);
    void start();
    void stop();
    void setEEGSampleRate(int);
    QList<QList<double>> getData();
    QWidget *getConnectWidget();
    QStringList getChannelName();
private slots:
    void receive();
    void ConnectDevice(QMap<QString,QVariant>);
    void serialErrorDeal(QSerialPort::SerialPortError);
signals:
    void readDataEEG(QList<double>);
    void connectSuccess();
    void error(int);
    void connectStatus(QString);
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
    //日志串口
//    QSerialPort *serial_log;
    void  initSerialData();
    void setSerialDataConnect();
    //解析
    DataAnalysis *analysis;
    void setAnalysisConnect();
    //编码
    Encode *encode;
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

#endif // AMPLIFER_H
