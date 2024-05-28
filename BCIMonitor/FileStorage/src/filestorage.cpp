#include "filestorage.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QDebug"
#include "QDateTime"
#include "storageconfig.h"
#include "QCoreApplication"
#include "QInputDialog"
#include "QTimer"
FileStorage::FileStorage(QObject *parent):QObject(parent)
{
    qRegisterMetaType<QList<double>>("QList<double>");
    qRegisterMetaType<QList<QList<double> >>("QList<QList<double>>");
    init();
    setConnect();
}

FileStorage::~FileStorage()
{
    if(storage==NULL)
    {
        delete storage;
    }

    if(eegdata_head==NULL)
    {
        free(eegdata_head);
        free(heart_head);
        free(filter_eeg_head);
    }
}
void FileStorage::append(QList<QList<double> > data)
{
    QList<double> eeg=data.at(0);
    QList<double> heart=data.at(1);
    //将数据复制到缓冲区
    //脑电
    memcpy(eegdata_end,eeg.toVector().data(),eeg.size()*8);
    eegdata_num+=eeg.size()/16;
    eegdata_end+=eeg.size();
    //心电
    memcpy(heart_end,heart.toVector().data(),heart.size()*8);
    heart_num+=heart.size()/3;
    heart_end+=heart.size();
}

void FileStorage::initTimer()
{
    timer=new QTimer();
    connect(timer,&QTimer::timeout,this,&FileStorage::save);
}
void FileStorage::start()
{
    if(!connect_game_status)
    {
        account=QInputDialog::getText(NULL,"文件名","");
        if(!account.isEmpty())
        {
           setFileNameMsg(account,0);
        }
    }
    if(!account.isEmpty())
    {
        if(stop_flag)
        {
            if(mode==0)
            {
                timer->start();
            }
            train_time++;
            QDir dir;
            QString save_path=this->user_dir+"/"+QString::number(train_time);
            if(!dir.exists(save_path))
            {
                dir.mkpath(save_path);
            }
            QDateTime datetime=QDateTime::currentDateTime();
            QString data=datetime.date().toString("yyyyMMdd");
            QString time=datetime.time().toString("hhmmss");
            QString filename=save_path+"/"+account+"_"+data+time+"_"+QString::number(game_id)+".mat";
            creatFile(filename);
            start_flag=true;
            pause_flag=false;
            stop_flag=false;
        }
        else
        {
            QString path=this->user_dir+"/"+QString::number(train_time);
            QDir dir(path);
            if(dir.exists())
                dir.removeRecursively();
            QString save_path=this->user_dir+"/"+QString::number(train_time);
            if(!dir.exists(save_path))
            {
                dir.mkpath(save_path);
            }
            QDateTime datetime=QDateTime::currentDateTime();
            QString data=datetime.date().toString("yyyyMMdd");
            QString time=datetime.time().toString("hhmmss");
            QString filename=save_path+"/"+account+"_"+data+time+"_"+QString::number(game_id)+".mat";
            creatFile(filename);
            stop_flag=false;
            stop_flag=true;
            start_flag=false;
        }
        if(pause_flag)
        {
            start_flag=true;
            pause_flag=false;
        }
    }

}
void FileStorage::pause()
{
    pause_flag=true;
    save();
}
void FileStorage::stop()
{
    if(mode==0)
    {
        timer->stop();
    }
    start_flag=false;
    stop_flag=true;
    save();
    storage->stop();
}
void FileStorage::setSampleNum(int value)
{
}
void FileStorage::setChannel_num(quint8 value)
{
    channel_num=value;
    storage->setChannelNum(value);
}

void FileStorage::setSrate(quint16 rate)
{
    storage->setSrate(rate);
    this->srate=rate;
}
void FileStorage::setChanlocs(QVariantList value)
{
    storage->setChanlocs(value);
}

void FileStorage::setFileNameMsg(QString account, int game_id)
{
    this->account=account;
    this->game_id=game_id;
    //获取训练次数
    this->user_dir=this->dir+"/"+account+"/"+QDate::currentDate().toString("yyyy-MM-dd");
    train_time=StorageConfig::getTrainTime(this->user_dir);
    //检测文件夹是否存在
    QDir dir;
    if(!dir.exists(this->user_dir))
    {
        dir.mkpath(this->user_dir);
    }
}

void FileStorage::append_eeg(QList<double> data)
{
    if(start_flag)
    {
        memcpy(eegdata_end,data.toVector().data(),data.size()*8);
        eegdata_num+=data.size()/channel_num;
        eegdata_end+=data.size();
        if(eegdata_num==(srate*StorageConfig::getTime()))
        {
            save();
        }
    }
}

void FileStorage::append_eeg(QList<double> raw_data, QList<double> filter_data)
{
    if(start_flag)
    {
        memcpy(eegdata_end,raw_data.toVector().data(),raw_data.size()*8);
        eegdata_num+=raw_data.size()/channel_num;
        eegdata_end+=raw_data.size();
        memcpy(filter_eeg_end,filter_data.toVector().data(),filter_data.size()*8);
        filter_eeg_num+=filter_data.size()/channel_num;
        filter_eeg_end+=filter_data.size();
        if(eegdata_num==(srate*StorageConfig::getTime()))
        {
            save();
        }
    }
}
void FileStorage::creatFile()
{
    //选择文件
    QString name=QFileDialog::getSaveFileName(NULL,"新建文件","",tr("mat(*.mat);;bin(*.bin);;txt(*.txt);;csv(*.csv)"));
    //建立文件
    QFile file(name);
    file.open(QIODevice::WriteOnly);
    file.close();

    if(name.isEmpty())
    {
        return;
    }
    creatFile(name);
}
void FileStorage::creatFile(QString name)
{
    this->stop_flag=false;
    storage->setFilename(name);
    QFileInfo info(name);
    QString filter_file_name=info.path()+"/"+info.baseName()+"_filter.mat";
    qDebug()<<filter_file_name;
    filter_storage->setFilename(filter_file_name);

}

void FileStorage::appendEvent(int type)
{
    storage->appendEvent(type,eegdata_num);
}
void FileStorage::init()
{
    this->heart_num=0;
    this->eegdata_num=0;
    this->filter_eeg_num=0;
    this->start_flag=false;
    this->pause_flag=false;
    this->stop_flag=true;
    this->mode=1;
    storage=new MatStorage;
    filter_storage=new MatStorage;
    initTimer();
    //初始化配置
    StorageConfig::init();
    //获取文件保存目录
    this->dir=StorageConfig::getSavePath();
    this->connect_game_status=StorageConfig::getConnectGameStatus();
    quint16 storage_time=StorageConfig::getTime();
    //毫秒级精确度
    this->timer->setTimerType(Qt::PreciseTimer);
    this->timer->setInterval(storage_time*1000);
    //初始化内存：内存大小64*1000*60*2
    //脑电信号
    eegdata_head=(double*)malloc(32*1000*8*storage_time);
    eegdata_end=eegdata_head;

    filter_eeg_head=(double*)malloc(32*1000*8*storage_time);
    filter_eeg_end=filter_eeg_head;
    qDebug()<<filter_eeg_head;
    //心电信号
    heart_head=(double*)malloc(4*100*8*storage_time);
    heart_end=heart_head;

}
void FileStorage::setConnect()
{
    setStorageConnect();
}
void FileStorage::setStorageConnect()
{
//    connect(this,&FileStorage::storageSignal,storage,&Storage::save,Qt::DirectConnection);
    connect(this,&FileStorage::stopSignal,storage,&Storage::stop,Qt::DirectConnection);
    connect(storage,&Storage::saveFinish,this,&FileStorage::saveFinish,Qt::DirectConnection);
    connect(storage,&Storage::mergeMsg,this,&FileStorage::mergeMsg,Qt::DirectConnection);
}

void FileStorage::save()
{
    storage->save(eegdata_head,eegdata_num);
    eegdata_end=eegdata_head;
    heart_end=heart_head;
    eegdata_num=0;
    heart_num=0;

    filter_storage->save(filter_eeg_head,filter_eeg_num);
    filter_eeg_end=filter_eeg_head;
    filter_eeg_num=0;

}
