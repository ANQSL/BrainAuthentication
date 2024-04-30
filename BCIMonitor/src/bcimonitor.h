#ifndef BCIMONITOR_H
#define BCIMONITOR_H

#include <QMainWindow>
#include "QToolBar"
#include "QtCharts/QChart"
#include "curvegroup.h"
#include "amplifier.h"
#include "filestorage.h"
#include "processdata.h"
#include "datacommunicate.h"
using namespace QtCharts;
QT_BEGIN_NAMESPACE
namespace Ui { class BCIMonitor; }
QT_END_NAMESPACE
class BCIMonitor : public QMainWindow
{
    Q_OBJECT
public:
    BCIMonitor(QWidget *parent = nullptr);
    ~BCIMonitor();
public slots:
    //存储
    void setFileMsg(QString,int);
    void start();
    void stop();
    //曲线
    void appendMarkEnemyBorn(QMap<QString,QString>);
    void appendMarkEnemyDie(QMap<QString,QString>);
    void appendMarkFireHit(QMap<QString,QString>);
    void appendMarkFireMiss(QMap<QString,QString>);
    void appendMarkCutHit(QMap<QString,QString>);
    //
    void appendMark(quint8);
signals:
    void downData(QString);
    void saveFinished(QString);
    //与存储模块的交互
    void setChannelNum(quint8);
    void setChanlocs(QVariantList);
    //mark信息
    void markChanged(quint8);
    //滤波数据
    void filterData(QList<double>);
private slots:
    void connectAmplifier();
private:

    //事件类型
    typedef  enum
    {
       EnemyBorn=0, //敌人刷新
       EnemyDie, //敌人死亡
       FireHit,  //开枪命中
       FireHitErr, //开枪命中错误
       FireMiss,  //开枪未命中
       CutHit,   //挥砍命中
       CutHitErr, //挥砍命中错误
    }EventType;
    Ui::BCIMonitor *ui;
    void init();
    void setConnect();
    //工具栏
    QToolBar *toolbar;
    QList<QAction *> toolButton;
    void initTool();
    void setToolConnet();
    void enableSample(bool);

    //状态栏
    QStatusBar *statusbar;
    void initStatus();

    //数据降采样
    ProcessData *processdata;
    void initProcessData();
    void setProcessDataConnect();
    //曲线
    CurveGroup *curvegroup;
    void initCurveGroup();
    void setCurve();
    void setCurveConnect();
    //存储模块
    FileStorage *filestorage;
    void initFileStorage();
    void setFileConnect();
    //采集模块
    Amplifier *amplifier;
    //定时更新采集器信息
    void initAmplifier();
    void setAmplifierConnect();

    //解码状态
    bool decode_status=false;

    DataCommunicate *datacommunicate=new DataCommunicate;


};
#endif // BCIMONITOR_H
