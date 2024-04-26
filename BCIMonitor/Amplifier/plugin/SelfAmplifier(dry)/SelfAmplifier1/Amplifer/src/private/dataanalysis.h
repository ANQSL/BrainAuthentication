#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QObject>

class DataAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit DataAnalysis(QObject *parent = nullptr);
    void append(QByteArray data);
    //解析
    void analysis();
    //找帧头
    bool findBufferHead();
    //找帧尾
    bool findBufferEnd(QByteArray &buffer);
    //解析EEG
    void analysisEEG(QByteArray buffer);
    void analysisEEGItem(QByteArray buffer,double &value,bool & off_indicate);
signals:
    //解析EEG完毕
    void finishedEEGData(QList<double>);
private:
    QByteArray receive_data;
    quint8 eeg_sample_num=5;
    quint8 eeg_num=16;

};

#endif // DATAANALYSIS_H
