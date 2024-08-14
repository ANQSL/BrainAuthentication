#include "bassvep.h"
#include "custommessagebox.h"
BASSVEP::BASSVEP(QObject *parent) : QObject(parent),bite_teeth_recognition(32)
{
    CustomMessageHandler::installMessageHandler();
    initBCIMonitor();
    initFilter();
    initControlFly();
    initSSVEPWidget();
    initTaskWidget();
    initIndexWidget();
    connect(bcimonitor,&BCIMonitor::filterData,this,[=](QList<double> data){
        std::vector<float> value(data.size());
        for(int i=0;i<data.size();i++)
        {
            value[i]=data[i];
        }
        login.append(value);

        bite_teeth_recognition.initBiteTeethThreshold(value);
        bite_teeth_recognition.append(value);
        //登录成功后开始使用咬牙控制无人机
        if (login.getLoginStatus())
        {
            if(bite_teeth_recognition.recognitionStatus())
            {
                if(bite_teeth_recognition.recognitionModel())
                {
                    int command=bite_teeth_recognition.recogntionCommand();
                    controlfly->sendCommand(command);
                    bite_teeth_recognition.setRecognitionModel(false);
                }
                else
                {
                    bool isok=bite_teeth_recognition.recogntion();
                    if(isok)
                    {
                        bite_teeth_recognition.setRecognitionModel(true);
                        controlfly->startControl();
                    }
                }
            }
        }
        
    });
    connect(taskwidget,&start_game::start,this,[=](){
        //brain_recognition.start();
        bite_teeth_recognition.start();
        login.setStatus(0);
        login.start();
        ssvep_widget->display(2);
    });
    connect(taskwidget, &start_game::collection, this, [=]() {
        login.setStatus(1);
        login.start();
        ssvep_widget->display(2);
    });
    indexwidget->showMaximized();
    //匹配识别Id
    connect(bcimonitor,&BCIMonitor::calculateResult,[=](QByteArray data){
        QString result(data);
        result=result.replace("}","");
        result=result.replace(" ","");
        int id=result.split(",")[0].split(":")[1].toInt();
        int count=result.split(",")[1].split(":")[1].toInt();
    });
    calculate_test.show();
    connect(indexwidget,&IndexWidget::tabChanged,this,[=](int index){
        if(index==2)
        {
            ssvep_widget->show();
            QTimer::singleShot(1500,[=](){
                ssvep_widget->setParent(taskwidget->getSSVEPWidget());
            });
        }
    });
    connect(&login, &Login::loginSuccessed, this, [=]() {
            QTimer::singleShot(1600, [=]() {
                controlfly->showControlWidget();
                });
        });
}

BASSVEP::~BASSVEP()
{
    delete bcimonitor;
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
