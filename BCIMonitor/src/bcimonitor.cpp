#include "bcimonitor.h"
#include <QDebug>
#include "ui_bcimonitor.h"
#include "QIcon"
#include "QFileDialog"
BCIMonitor::BCIMonitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BCIMonitor)
{
    ui->setupUi(this);
    init();
    setConnect();
}

BCIMonitor::~BCIMonitor()
{
    delete ui;
    delete filestorage;
    delete amplifier;
    delete processdata;
    delete datacommunicate;
}

void BCIMonitor::connectAmplifier()
{
    QWidget *connectwidget=amplifier->getConnectWidget();
    if(connectwidget==NULL)
    {
        QMessageBox::about(this,"消息提示","请加载放大器");
    }
    else
    {
        connectwidget->show();
    }
}
void BCIMonitor::setFileMsg(QString account, int game_id)
{
    filestorage->setFileNameMsg(account,game_id);
}

void BCIMonitor::start()
{
    filestorage->start();
}

void BCIMonitor::stop()
{
    filestorage->stop();
}

void BCIMonitor::appendMarkEnemyBorn(QMap<QString, QString>)
{
    curvegroup->appendMark("敌人刷新");
    filestorage->appendEvent(EventType::EnemyBorn);
}

void BCIMonitor::appendMarkEnemyDie(QMap<QString, QString>)
{
    curvegroup->appendMark("敌人死亡");
     filestorage->appendEvent(EventType::EnemyDie);
}

void BCIMonitor::appendMarkFireHit(QMap<QString, QString> map)
{
    if(map["HitRight"].toInt()==1)
    {
        curvegroup->appendMark("开枪命中");
        filestorage->appendEvent(EventType::FireHit);
    }
    else
    {
       curvegroup->appendMark("命中错误");
       filestorage->appendEvent(EventType::FireHitErr);
    }
}

void BCIMonitor::appendMarkFireMiss(QMap<QString, QString>)
{
    curvegroup->appendMark("开枪未命中");
    filestorage->appendEvent(EventType::FireMiss);
}

void BCIMonitor::appendMarkCutHit(QMap<QString, QString> map)
{
    if(map["HitRight"].toInt()==1)
    {
        curvegroup->appendMark("挥砍命中");
        filestorage->appendEvent(EventType::CutHit);
    }
    else
    {
       curvegroup->appendMark("命中错误");
       filestorage->appendEvent(EventType::CutHitErr);
    }
}

void BCIMonitor::appendMark(quint8 type)
{
    curvegroup->appendMark(QString(type));
    filestorage->appendEvent(type);
}
void BCIMonitor::init()
{
    initTool();
    initStatus();
    initCurveGroup();
    initFileStorage();
    initAmplifier();
    initProcessData();
}

void BCIMonitor::setConnect()
{
    setToolConnet();
    setProcessDataConnect();
    setFileConnect();
    setAmplifierConnect();
}

void BCIMonitor::initTool()
{
   toolbar=new QToolBar();
   this->addToolBar(toolbar);
   toolbar->addAction(QIcon(":/start.png"),"");
   toolbar->addAction(QIcon(":/pause.png"),"");
   toolbar->addAction(QIcon(":/stop.png"),"");
   toolbar->addAction(QIcon(":/last.png"),"");
   toolbar->addAction(QIcon(":/next.png"),"");
   toolbar->addAction(QIcon(":/IncreaseChannel.png"),"");
   toolbar->addAction(QIcon(":/ReduceChannel.png"),"");
   toolbar->addAction(QIcon(":/Increasescale.png"),"");
   toolbar->addAction(QIcon(":/Reducescale.png"),"");
   toolbar->addAction(QIcon(":/decode.png"),"");
   toolbar->addAction(QIcon(":/connect.png"),"");
   toolbar->addAction(QIcon(":/plugin.png"),"");
   toolButton=toolbar->actions();
   enableSample(false);
}

void BCIMonitor::setToolConnet()
{
    connect(toolButton[0],&QAction::triggered,filestorage,&FileStorage::start);
    connect(toolButton[1],&QAction::triggered,filestorage,&FileStorage::pause);
    connect(toolButton[2],&QAction::triggered,filestorage,&FileStorage::stop);

    connect(toolButton[0],&QAction::triggered,amplifier,&Amplifier::start);
    connect(toolButton[1],&QAction::triggered,amplifier,&Amplifier::pause);
    connect(toolButton[2],&QAction::triggered,amplifier,&Amplifier::stop);
    connect(toolButton[10],&QAction::triggered,this,&BCIMonitor::connectAmplifier);
    connect(toolButton[9],&QAction::triggered,this,[=](){
        if(decode_status)
        {
            decode_status=!decode_status;
            amplifier->setDecodeStatus(decode_status);
            toolButton[9]->setIcon(QIcon(":/decode.png"));
        }
        else {
            decode_status=!decode_status;
            amplifier->setDecodeStatus(decode_status);
            toolButton[9]->setIcon(QIcon(":/encode.png"));
        }
    });
    connect(toolButton[11],&QAction::triggered,amplifier,&Amplifier::showPluginWidget);
}
void BCIMonitor::enableSample(bool enable)
{
    for(int i=0;i<10;i++)
    {
        toolButton[i]->setEnabled(enable);
    }
}

void BCIMonitor::initStatus()
{
    statusbar=new QStatusBar;
    this->setStatusBar(statusbar);
}

void BCIMonitor::initProcessData()
{
    processdata=new ProcessData;
    processdata->setDownRate(20);
}

void BCIMonitor::setProcessDataConnect()
{
    connect(processdata,&ProcessData::downData,this,&BCIMonitor::downData);
}
void BCIMonitor::initCurveGroup()
{
    curvegroup=NULL;

}

void BCIMonitor::setCurve()
{
    if(curvegroup!=NULL)
    {
        delete curvegroup;
        curvegroup=NULL;
    }
    curvegroup=new CurveGroup();
    this->setCentralWidget(curvegroup);
    curvegroup->setSrate(amplifier->getSampleRate());
    setCurveConnect();
    QStringList labels=amplifier->getChannelName();
    curvegroup->setCurveLabels(labels);
    curvegroup->setCurveNum(labels.size());

}

void BCIMonitor::setCurveConnect()
{
    connect(toolButton[3],&QAction::triggered,curvegroup,&CurveGroup::last);
    connect(toolButton[4],&QAction::triggered,curvegroup,&CurveGroup::next);
    connect(toolButton[5],&QAction::triggered,curvegroup,&CurveGroup::increaseGroupChannel);
    connect(toolButton[6],&QAction::triggered,curvegroup,&CurveGroup::reduceGroupChannel);
    connect(toolButton[7],&QAction::triggered,curvegroup,&CurveGroup::increaseScale);
    connect(toolButton[8],&QAction::triggered,curvegroup,&CurveGroup::reduceScale);
    connect(amplifier,SIGNAL(readyRead(QList<double>)),curvegroup,SLOT(append(QList<double>)));
}
void BCIMonitor::initFileStorage()
{
    filestorage=new FileStorage();
}

void BCIMonitor::setFileConnect()
{
    connect(this,&BCIMonitor::setChannelNum,filestorage,&FileStorage::setChannel_num);
    connect(this,&BCIMonitor::setChanlocs,filestorage,&FileStorage::setChanlocs);
    connect(filestorage,&FileStorage::saveFinish,this,&BCIMonitor::saveFinished);
    connect(filestorage,&FileStorage::mergeMsg,this,[=](QString msg){
        statusbar->showMessage(msg);
    });
}
void BCIMonitor::initAmplifier()
{
    amplifier=new Amplifier();
}

void BCIMonitor::setAmplifierConnect()
{
    //数据
    //存储模块
    connect(amplifier,SIGNAL(rawDataFinished(QList<double>)),filestorage,SLOT(append_eeg(QList<double>)));
//    降采样
    connect(amplifier,SIGNAL(readyRead(QList<double>)),processdata,SLOT(receiveData(QList<double>)));
    connect(amplifier,SIGNAL(rawDataFinished(QList<double>)),datacommunicate,SLOT(append(QList<double>)));
    //插件
    connect(amplifier,&Amplifier::loadPluginSucceed,this,[=](){
            emit setChannelNum(amplifier->getChannelName().size());
            filestorage->setChanlocs(amplifier->getChanlocs());
            filestorage->setSrate(amplifier->getSampleRate());
            processdata->setSrate(amplifier->getSampleRate());

            processdata->seteeggame_index(amplifier->getEEGGameIndex());
            processdata->setMuscleIndex(amplifier->getMuscleIndex());
            processdata->setBreathIndex(amplifier->getBreathIndex());
            processdata->setHeartIndex(amplifier->getHeartIndex());
            setCurve();

            datacommunicate->setSrate(amplifier->getSampleRate());
    });
    //采集器连接成功
    connect(amplifier,&Amplifier::connected,this,[=](){
        amplifier->getConnectWidget()->hide();
        enableSample(true);
//        setCurve();
    });
    connect(amplifier,&Amplifier::disconnected,this,[=](){
        enableSample(false);
        QMessageBox::about(this,"消息提示","设备断开");
    });
}


