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
    delete monitorConfigWidget;
}

void BCIMonitor::connectHost()
{
    datacommunicate->buildConnection();
}

void BCIMonitor::startDataTransmit()
{
    datacommunicate->start();
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
//    qDebug()<<"当前时间戳"<<QDateTime::currentMSecsSinceEpoch();
    if(amplifier->getStatus())
    {
        curvegroup->appendMark(QString(type));
        qDebug()<<"接收mark为:"<<type;
        filestorage->appendEvent(type);
        emit markChanged(type);
    }

}
void BCIMonitor::init()
{
    initTool();
    initStatus();
    initCurveGroup();
    initFileStorage();
    initAmplifier();
    initProcessData();
    initMonitorConfigWidget();
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
   toolbar=new MonitorToolBar;
   this->addToolBar(toolbar);
}

void BCIMonitor::setToolConnet()
{
    connect(toolbar,&MonitorToolBar::startSignal,filestorage,&FileStorage::start);
    connect(toolbar,&MonitorToolBar::pauseSignal,filestorage,&FileStorage::pause);
    connect(toolbar,&MonitorToolBar::stopSignal,filestorage,&FileStorage::stop);

    connect(toolbar,&MonitorToolBar::monitorSignal,amplifier,&Amplifier::start);
    connect(toolbar,&MonitorToolBar::stopmonitorSignal,amplifier,&Amplifier::stop);
    connect(toolbar,&MonitorToolBar::connectSignal,this,&BCIMonitor::connectAmplifier);
    connect(toolbar,&MonitorToolBar::encodeSignal,this,[=](){
            decode_status=false;
            amplifier->setDecodeStatus(decode_status);
    });
    connect(toolbar,&MonitorToolBar::decodeSignal,this,[=](){
            decode_status=true;
            amplifier->setDecodeStatus(decode_status);
    });
    connect(toolbar,&MonitorToolBar::pluginSignal,amplifier,&Amplifier::showPluginWidget);
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
    connect(toolbar,&MonitorToolBar::lastSignal,curvegroup,&CurveGroup::last);
    connect(toolbar,&MonitorToolBar::nextSignal,curvegroup,&CurveGroup::next);
    connect(toolbar,&MonitorToolBar::increaseChannelSignal,curvegroup,&CurveGroup::increaseGroupChannel);
    connect(toolbar,&MonitorToolBar::ReduceChannelSignal,curvegroup,&CurveGroup::reduceGroupChannel);
    connect(toolbar,&MonitorToolBar::increasescaleSignal,curvegroup,&CurveGroup::increaseScale);
    connect(toolbar,&MonitorToolBar::ReducescaleSignal,curvegroup,&CurveGroup::reduceScale);
    connect(toolbar,&MonitorToolBar::ReducedotSignal,curvegroup,&CurveGroup::reduceXRange);
    connect(toolbar,&MonitorToolBar::increasedotSignal,curvegroup,&CurveGroup::increaseXRange);
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
    connect(amplifier,SIGNAL(readyRead(QList<double>,QList<double>)),filestorage,SLOT(append_eeg(QList<double>,QList<double>)));
//    降采样
    connect(amplifier,SIGNAL(readyRead(QList<double>)),processdata,SLOT(receiveData(QList<double>)));
    connect(amplifier,QOverload<QList<double>>::of(&Amplifier::readyRead),this,&BCIMonitor::filterData);
    //通信
    //原始数据
//    connect(amplifier,SIGNAL(rawDataFinished(QList<double>)),datacommunicate,SLOT(append(QList<double>)));
    //滤波数据
    connect(amplifier,SIGNAL(readyRead(QList<double>)),datacommunicate,SLOT(append(QList<double>)));
    connect(datacommunicate,&DataCommunicate::readMark,this,&BCIMonitor::appendMark);
    connect(datacommunicate,&DataCommunicate::result,this,&BCIMonitor::calculateResult);
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
        toolbar->enableAction();
//        setCurve();
    });
    connect(amplifier,&Amplifier::disconnected,this,[=](){
        toolbar->disabledAction();
        QMessageBox::about(this,"消息提示","设备断开");
    });
}

void BCIMonitor::initMonitorConfigWidget()
{
    monitorConfigWidget=new MonitorConfigWidget;
    monitorConfigWidget->setWindowFlag(Qt::Dialog);


//    monitorConfigWidget->addConfigWidget(curvegroup->getCurveconfigwidget(),"信号显示");
    monitorConfigWidget->addConfigWidget(filestorage->getStorageconfigwidget(),"文件保存");
    connect(toolbar,&MonitorToolBar::settingSignal,this,[=](){
        monitorConfigWidget->exec();
    });
}


