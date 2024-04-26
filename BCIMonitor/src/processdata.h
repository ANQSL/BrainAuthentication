#ifndef PROCESSDATA_H
#define PROCESSDATA_H

#include <QObject>

class ProcessData : public QObject
{
    Q_OBJECT
public:
    explicit ProcessData(QObject *parent = nullptr);
    void setDownRate(quint16 value);
    void setSrate(const quint16 &value);

    void seteeggame_index(QList<uint8_t>);//EEG游戏索引, 12个通道
    void setMuscleIndex(QList<uint8_t>);
    void setBreathIndex(QList<uint8_t>);
    void setHeartIndex(QList<uint8_t>);

    void clear();


public slots:
    void receiveData(QList<double>);
signals:
    void downData(QString);
private:
    QVector<QList<double>> data;
    QList<uint8_t> eeggame_index;//12个通道
//    QList<uint8_t> other_index;
    QList<uint8_t> muscle_index;
    QList<uint8_t> breath_index;
    QList<uint8_t> heart_index;
    quint16 down_sample;
    quint16 downrate;
};

#endif // PROCESSDATA_H
