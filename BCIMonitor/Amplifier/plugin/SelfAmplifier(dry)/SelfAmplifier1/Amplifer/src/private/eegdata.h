#ifndef EEGDATA_H
#define EEGDATA_H

#include "QObject"
class EEGData:public QObject
{
    Q_OBJECT
public:
    EEGData();
    QList<QList<double>> getData();
public slots:
    void append(QList<double> data,QList<bool>);
private:
    QList<double> data;
    QList<bool> off_indicate;
};

#endif // EEGDATA_H
