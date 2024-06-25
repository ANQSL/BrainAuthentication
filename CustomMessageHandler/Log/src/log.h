#ifndef LOG_H
#define LOG_H

#include <QObject>
#include "QFile"
class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);
    void save(QString);
    void save(QString type,QString data);
signals:
private:
    //软件启动次数
    quint32 start_time;
    void readStartTime();
};

#endif // LOG_H
