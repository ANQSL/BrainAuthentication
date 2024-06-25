#include "bassvep.h"
#include "custommessagebox.h"
BASSVEP::BASSVEP(QObject *parent) : QObject(parent)
{
    CustomMessageHandler::installMessageHandler();
    initCCA();
    initBCIMonitor();
    initFilter();
    initControlFly();
    initSSVEPWidget();
    initTaskWidget();
    initIndexWidget();
//    connect(bcimonitor,&BCIMonitor::markChanged,cca,&CCA::start);
    connect(bcimonitor,&BCIMonitor::filterData,this,[=](QList<double> data){
        data=filter->filter(data);
        cca->append(data);
    });
    connect(cca,&CCA::result,controlfly,&ControlFly::command);
    connect(taskwidget,&start_game::start,this,[=](){
        QTimer::singleShot(1000,[=](){
            ssvep_widget->display(1);
            cca->start();
            bcimonitor->startDataTransmit();
        });

    });
    connect(taskwidget,&start_game::collection,this,[=](){
        QTimer::singleShot(1000,[=](){
            ssvep_widget->display(2);
            cca->start();
            bcimonitor->startDataTransmit();
        });

    });
    indexwidget->showMaximized();

    //算法测试
    connect(cca,&CCA::result,&calculate_test,&CalculateTest::appendSSVEP);
    //匹配识别Id
    connect(bcimonitor,&BCIMonitor::calculateResult,[=](QByteArray data){
        QString result(data);
        result=result.replace("}","");
        result=result.replace(" ","");
        int id=result.split(",")[0].split(":")[0].toInt();
        int count=result.split(",")[1].split(":")[1].toInt();
        if(id==-1)
        {
            //登录失败
            CustomMessageBox::show(NULL,"登录失败");
            qDebug()<<QString("MsgType=test,data=登录失败");
        }
        else if(count>=100)
        {
            //登录成功
            login_time=0;
            CustomMessageBox::show(NULL,"登录成功");
            calculate_test.appendRecognition(id);
            qDebug()<<QString("MsgType=test,data=登录成功 id=%1").arg(id);
        }
        else
        {
            //注意力不集中
            login_time++;
            if(login_time>=3)
            {
                //登录失败
                login_time=0;
                CustomMessageBox::show(NULL,"失败三次,登录失败");
                qDebug()<<QString("MsgType=test,data=登录失败");
            }
            else
            {
               CustomMessageBox::show(NULL,"注意力不集中，请重试");
            }

        }
    });
    calculate_test.show();
    ssvep_widget->start();
    connect(indexwidget,&IndexWidget::tabChanged,this,[=](int index){
        if(index==2)
        {
            ssvep_widget->show();
            QTimer::singleShot(1500,[=](){
                ssvep_widget->setParent(taskwidget->getSSVEPWidget());
            });
        }
//
    });
}

BASSVEP::~BASSVEP()
{
    delete bcimonitor;
    delete cca;
    delete filter;
    delete controlfly;
    delete ssvep_widget;
    delete indexwidget;
}

void BASSVEP::initFilter()
{
    filter=new DataProcess::Filter;
    filter->init(32,1000,1,15);
}

void BASSVEP::initBCIMonitor()
{
    bcimonitor=new BCIMonitor;
    bcimonitor->setFileMsg("lx",123);
}

void BASSVEP::initControlFly()
{
    controlfly=new ControlFly;
}

void BASSVEP::initSSVEPWidget()
{
    ssvep_widget=new SSVEPWidget;
}

void BASSVEP::initIndexWidget()
{
    indexwidget=new IndexWidget;
    indexwidget->addWidget("采集",bcimonitor);
    indexwidget->addWidget("任务",taskwidget);
    //    indexwidget->addWidget("任务");
}

void BASSVEP::initTaskWidget()
{
    taskwidget=new start_game;
}
void BASSVEP::initCCA()
{
    cca=new CCA;
}
