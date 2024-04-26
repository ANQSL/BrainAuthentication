#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QObject>
#include "QThread"
#include "QSerialPort"
#define  FRAMELEN 51
class DataAnalysis : public QThread
{
    Q_OBJECT
public:
    explicit DataAnalysis(QObject *parent = nullptr);
    void setSerial(QSerialPort *serial);
    void start();
    void destory();
    void append(QByteArray);
private:
    //解析
    void analysis();
    //找帧头
    bool findBufferHead();
    //解析EEG
//    QList<QList<double>> analysisEEG(QByteArray);
    void analysisEEG(QByteArray);
    void run() override;
    QByteArray readFrame();
    bool readData();

    //倒序
    QList<double> reverse(QList<double> data);
signals:
    //解析EEG完毕
    void finishedEEGData(QList<double>);
private:
    QSerialPort *serial;//串口
    bool status; //线程状态
    QByteArray buffer; //缓冲区
    QByteArray frames;//帧缓冲区
};

#endif // DATAANALYSIS_H
