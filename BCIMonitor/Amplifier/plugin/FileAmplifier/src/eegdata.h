#ifndef EEGDATA_H
#define EEGDATA_H

#include "QObject"
class EEGData:public QObject
{
    Q_OBJECT
public:
    EEGData();
    ~EEGData();
    QList<QList<double>> getData();
    void clear();
public slots:
    void setData(void *data,quint32 length,quint8 channel_num);
private:
    double  *data;
    quint8  point_num;
    quint32 current_index;
    quint32 data_length;
    quint8 channel_num;
};

#endif // EEGDATA_H
