#ifndef FILESTORAGE_H
#define FILESTORAGE_H
#include "QString"
#include "matstorage.h"
//#include "binstorage.h"
//#include "txtstorage.h"
//#include "csvstorage.h"
#include "QThread"
class FileStorage:public QObject
{
    Q_OBJECT
public:
    explicit FileStorage(QObject *parent=nullptr);
    ~FileStorage();
    //新建文件
    void creatFile();
    void creatFile(QString);
    //插入事件
    void appendEvent(int);
public slots:
    //开始
    void start();
    //暂停
    void pause();
    //结束
    void stop();
    //设置采样点
    void setSampleNum(int value);
    //设置通道数
    void setChannel_num(quint8 value);
    //设置采样率
    void setSrate(quint16 srate);
    //设置脑电导联分布信息
    void setChanlocs(QVariantList);
    //设置文件信息(账户和游戏)
    void setFileNameMsg(QString account,int game_id);
    //数据插入
    void append_eeg(QList<double> data);
    void append(QList<QList<double>> data);
private:
    //暂停标志
    bool  pause_flag;
    //开始标志
    bool  start_flag;
    //结束标志
    bool  stop_flag;
    //存储过程
    Storage *storage;
    //文件保存路径
    QString dir;
    QString user_dir;
    //被试ID
    QString account;
    //任务Id
    int game_id;
    //脑电数据头指针
    double* eegdata_head;
    //脑电数据尾指针
    double* eegdata_end;
    //脑电数据计数
    quint32 eegdata_num;
    //脑电通道数
    quint8 channel_num;
    //心电数据头指针
    double *heart_head;
    //心电尾指针
    double *heart_end;
    //心电数据计数
    quint32 heart_num;

    QTimer *timer;
    void initTimer();
    void init();
    void setConnect();
    void setStorageConnect();
    void save();
    //训练次数
    int train_time;
    //是否连接游戏
    bool connect_game_status;
signals:
    void storageSignal(double*,int num);
    void setNameSignal(QString);
    void stopSignal();
    void saveFinish(QString);
    void mergeMsg(QString);
};
#endif // FILESTORAGE_H
