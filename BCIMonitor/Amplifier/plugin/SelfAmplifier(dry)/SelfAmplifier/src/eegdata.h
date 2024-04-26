#ifndef EEGDATA_H
#define EEGDATA_H

#include "QObject"
#include "QMutex"
class EEGData:public QObject
{
    Q_OBJECT
public:
    EEGData();
    QList<QList<double>> getData();
    void clear();
public slots:
    void append(QList<double> data);
private:
    QMutex mutex;
    QList<QList<double>> data;
    quint8  point_num;
};

#endif // EEGDATA_H
