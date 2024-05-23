#ifndef DATASEND_H
#define DATASEND_H

#include <QObject>
#include "tcpcommunicate.h"
#define BufferLEN 25600000
class DataCommunicate : public QObject
{
    Q_OBJECT
public:
    explicit DataCommunicate(QObject *parent = nullptr);
    ~DataCommunicate();
    void setSrate(quint16);
    void start();
    void stop();

    void clear();

    void buildConnection();
    void disconnection();
public slots:
    void append(QList<double>);
signals:
    void result(int);
    void readMark(quint8);
private:
    quint16 srate;
    //数据
    double *buffer;//缓冲区头
    double *current_point;//当前缓冲区位置
    quint16 buffer_data_size;
    //tcp发送
    TcpCommunicate *communicate;
    void initCommunicate();
    //发送标志
    bool send_status=false;

    int send_time=0;

};

#endif // DATASEND_H
