#include "ssvep.h"
#include "QGuiApplication"
#include "QScreen"
#include "math.h"
#include "QPainter"
#include "QKeyEvent"
#include "QDebug"
#define PI acos(-1)
SSVEP::SSVEP()
{
    initGrayWeight();
    initTimer();
}
SSVEP::~SSVEP()
{

}

void SSVEP::paintEvent(QPaintEvent *event)
{
    if(type)
    {
       if(current_frame!=gray_weight.size())
       {
           display();
       }
       else
       {
           timer->stop();
           current_frame=0;
           type=false;
           initWidget();
       }
    }
    else
    {
        initWidget();
    }
}

void SSVEP::keyPressEvent(QKeyEvent *event)
{
    type=true;
    timer->start(16);
}

void SSVEP::initWidget()
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    //上四个方块
    painter.fillRect(20,20,50,50,Qt::white);
    painter.fillRect((width()-40)/3-25,20,50,50,Qt::white);
    painter.fillRect((width()-40)/3*2-25,20,50,50,Qt::white);
    painter.fillRect((width()-40)-25,20,50,50,Qt::white);
    //中二个方块
    painter.fillRect(20,height()/2-25,50,50,Qt::white);
    painter.fillRect((width()-40)-25,height()/2-25,50,50,Qt::white);
    //下四个方块
    painter.fillRect(20,height()-70,50,50,Qt::white);
    painter.fillRect((width()-40)/3-25,height()-70,50,50,Qt::white);
    painter.fillRect((width()-40)/3*2-25,height()-70,50,50,Qt::white);
    painter.fillRect((width()-40)-25,height()-70,50,50,Qt::white);

    QFont font("Arial", 20);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(15+20,35+20,"0");
    painter.drawText((width()-40)/3-25+15,20+35,"1");
    painter.drawText((width()-40)/3*2-25+15,20+35,"2");
    painter.drawText((width()-40)-25+15,35+20,"3");

    painter.drawText(20+15,height()/2-25+35,"4");
    painter.drawText((width()-40)-25+15,height()/2-25+35,"5");

    painter.drawText(15+20,height()-70+35,"6");
    painter.drawText((width()-40)/3-25+15,height()-70+35,"7");
    painter.drawText((width()-40)/3*2-25+15,height()-70+35,"8");
    painter.drawText((width()-40)-25+15,height()-70+35,"9");
}

void SSVEP::display()
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    int i=current_frame;
    //上四个方块
    painter.fillRect(20,20,50,50,qRgb(gray_weight[i][0],gray_weight[i][0],gray_weight[i][0]));
    painter.fillRect((width()-40)/3-25,20,50,50,qRgb(gray_weight[i][1],gray_weight[i][1],gray_weight[i][1]));
    painter.fillRect((width()-40)/3*2-25,20,50,50,qRgb(gray_weight[i][2],gray_weight[i][2],gray_weight[i][2]));
    painter.fillRect((width()-40)-25,20,50,50,qRgb(gray_weight[i][3],gray_weight[i][3],gray_weight[i][3]));
    //中二个方块
    painter.fillRect(20,height()/2-25,50,50,qRgb(gray_weight[i][4],gray_weight[i][4],gray_weight[i][4]));
    painter.fillRect((width()-40)-25,height()/2-25,50,50,qRgb(gray_weight[i][5],gray_weight[i][5],gray_weight[i][5]));
    //下四个方块
    painter.fillRect(20,height()-70,50,50,qRgb(gray_weight[i][6],gray_weight[i][6],gray_weight[i][6]));
    painter.fillRect((width()-40)/3-25,height()-70,50,50,qRgb(gray_weight[i][7],gray_weight[i][7],gray_weight[i][7]));
    painter.fillRect((width()-40)/3*2-25,height()-70,50,50,qRgb(gray_weight[i][8],gray_weight[i][8],gray_weight[i][8]));
    painter.fillRect((width()-40)-25,height()-70,50,50,qRgb(gray_weight[i][8],gray_weight[i][8],gray_weight[i][8]));

    QFont font("Arial", 20);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(15+20,35+20,"0");
    painter.drawText((width()-40)/3-25+15,20+35,"1");
    painter.drawText((width()-40)/3*2-25+15,20+35,"2");
    painter.drawText((width()-40)-25+15,35+20,"3");

    painter.drawText(20+15,height()/2-25+35,"4");
    painter.drawText((width()-40)-25+15,height()/2-25+35,"5");

    painter.drawText(15+20,height()-70+35,"6");
    painter.drawText((width()-40)/3-25+15,height()-70+35,"7");
    painter.drawText((width()-40)/3*2-25+15,height()-70+35,"8");
    painter.drawText((width()-40)-25+15,height()-70+35,"9");
    current_frame++;
}
void SSVEP::initGrayWeight()
{
    QScreen *screen= QGuiApplication::primaryScreen();
    int refreshRate=screen->refreshRate();
    if(refreshRate==60)
    {
        QList<QVariant> filckerFrep=config.filckerFrep;
        QList<QVariant> filckerPhi=config.filckerPhi;
        int filcker_num=filckerFrep.size();
        quint16 display_time=(config.display_time/1000)+1;
        quint16 frame_num=display_time*refreshRate;
        for(int i=0;i<frame_num;i++)
        {
            QList<quint8> frame_data;
            for(int j=0;j<filcker_num;j++)
            {
                quint8 data=255*0.5*(1+sin(2*PI*filckerFrep[j].toDouble()*((i+1)/(refreshRate*1.0))+filckerPhi[j].toDouble()*PI));
                frame_data.append(data);
            }
            this->gray_weight.append(frame_data);
        }
    }
}

void SSVEP::initTimer()
{
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
}
