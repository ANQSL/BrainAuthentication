#include "ssvep.h"
#include "QGuiApplication"
#include "QScreen"
#include "math.h"
#include "QPainter"
#include "QKeyEvent"
#include "QRandomGenerator"
#include "QTime"
#include "timerevent.h"
#include "iostream"
#include "QtConcurrent/QtConcurrent"
#include "QDateTime"
#define PI acos(-1)
SSVEP::SSVEP()
{
    this->setWindowFlags(Qt::Tool|Qt::WindowStaysOnTopHint);
    QtConcurrent::run(this, &SSVEP::readInput);
    connect(this,&SSVEP::newCommand,this,&SSVEP::readCommand);
    initGrayWeight();
    initTimer();
    initMarks();
    initCommunication();
    this->resize(1600,800);
    initFrames();
}
SSVEP::~SSVEP()
{
    delete communication;
    timer->stop();
    read_status=false;
    QThread::usleep(50);
    delete timer;
}
void SSVEP::paintEvent(QPaintEvent *event)
{
    if(type)
    {
       quint64 end_time=QDateTime::currentMSecsSinceEpoch();
       if((end_time-start_time)<=5000)
       {
             QPainter painter(this);
             painter.drawPixmap(this->rect(),frames[current_frame]);
//             painter.fillRect(rect(), Qt::black);
//             display(painter,current_frame);
             current_frame++;
       }
       else
       {
           timer->stop();
           print("开销时间为："+QString::number(QDateTime::currentMSecsSinceEpoch()-start_time));
           current_frame=0;
           type=false;
           current_task_num++;
           if(current_task_num==marks.size())
           {
               current_task_num=0;
           }
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
    communication->connectAmplifier();
    type=true;
    print("第"+QString::number(current_task_num+1)+"次任务");
    if(mode)
    {
       initFrames(marks[current_task_num]);
       print("当前频率："+QString::number(config.filckerFrep[marks[current_task_num]].toFloat()));
       emit markChanged(marks[current_task_num]+1);
    }
    start_time=QDateTime::currentMSecsSinceEpoch();
    timer->start(16);
}

void SSVEP::drawArrows(QPainter &painter,int x, int y, QColor color,Direction m_direction)
{

    // 计算箭头路径
    QPainterPath path;
    int bias=150;
    int arrow_bias=50;
    switch (m_direction) {
       case Up:
            {
                path.moveTo(x-bias/2, y-bias/2);
                path.lineTo(x-bias/2, y+bias/2);
                path.lineTo(x+bias/2,y+bias/2);
                path.lineTo(x+bias/2,y-bias/2);
                path.lineTo(x+bias/2+arrow_bias,y-bias/2);
                double y_=(bias/2+arrow_bias)*tan(PI/6);
                path.lineTo(x,y-bias/2-y_);
                path.lineTo(x-bias/2-arrow_bias,y-bias/2);
                path.lineTo(x-bias/2, y-bias/2);
            }
           break;
       case Down:
            {
                path.moveTo(x-bias/2, y-bias/2);
                path.lineTo(x-bias/2,y+bias/2);
                path.lineTo(x-bias/2-arrow_bias,y+bias/2);
                double y_=(bias/2+arrow_bias)*tan(PI/6);
                path.lineTo(x,y+bias/2+y_);
                path.lineTo(x+bias/2+arrow_bias,y+bias/2);
                path.lineTo(x+bias/2,y+bias/2);
                path.lineTo(x+bias/2,y-bias/2);
                path.lineTo(x-bias/2, y-bias/2);
            }
           break;
       case Left:
            {
                path.moveTo(x-bias/2, y-bias/2);
                path.lineTo(x-bias/2,y-bias/2-arrow_bias);
                double x_=(bias/2+arrow_bias)*tan(PI/6);
                path.lineTo(x-bias/2-x_,y);
                path.lineTo(x-bias/2,y+bias/2+arrow_bias);
                path.lineTo(x-bias/2,y+bias/2);
                path.lineTo(x+bias/2,y+bias/2);
                path.lineTo(x+bias/2,y-bias/2);
                path.lineTo(x-bias/2, y-bias/2);
            }
           break;
       case Right:
            {

                path.moveTo(x-bias/2, y-bias/2);
                path.lineTo(x-bias/2,y+bias/2);
                path.lineTo(x+bias/2,y+bias/2);
                path.lineTo(x+bias/2,y+bias/2+arrow_bias);
                double x_=(bias/2+arrow_bias)*tan(PI/6);
                path.lineTo(x+bias/2+x_,y);
                path.lineTo(x+bias/2,y-bias/2-arrow_bias);
                path.lineTo(x+bias/2,y-bias/2);
                path.lineTo(x-bias/2, y-bias/2);
            }
           break;
       default:
           break;
    }

    // 填充箭头内部为白色
    painter.setBrush(color);
    painter.drawPath(path);
    painter.fillPath(path, color);
}

void SSVEP::print(QString msg)
{
    std::string data=msg.toStdString();
    std::cout<<data;
    std::cout.flush();
}

void SSVEP::initWidget()
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    drawArrows(painter,width()/2,150,Qt::white,Up);
    drawArrows(painter,width()/2,height()-150,Qt::white,Down);
    drawArrows(painter,150,height()/2,Qt::white,Left);
    drawArrows(painter,width()-150,height()/2,Qt::white,Right);
//    //上四个方块
//    painter.fillRect(20,20,50,50,Qt::white);
//    painter.fillRect((width()-40)/3-25,20,50,50,Qt::white);
//    painter.fillRect((width()-40)/3*2-25,20,50,50,Qt::white);
//    painter.fillRect((width()-40)-25,20,50,50,Qt::white);
//    //中二个方块
//    painter.fillRect(20,height()/2-25,50,50,Qt::white);
//    painter.fillRect((width()-40)-25,height()/2-25,50,50,Qt::white);
//    //下四个方块
//    painter.fillRect(20,height()-70,50,50,Qt::white);
//    painter.fillRect((width()-40)/3-25,height()-70,50,50,Qt::white);
//    painter.fillRect((width()-40)/3*2-25,height()-70,50,50,Qt::white);
//    painter.fillRect((width()-40)-25,height()-70,50,50,Qt::white);

//    QFont font("Arial", 20);
//    painter.setFont(font);
//    painter.setPen(Qt::black);
//    painter.drawText(15+20,35+20,"0");
//    painter.drawText((width()-40)/3-25+15,20+35,"1");
//    painter.drawText((width()-40)/3*2-25+15,20+35,"2");
//    painter.drawText((width()-40)-25+15,35+20,"3");

//    painter.drawText(20+15,height()/2-25+35,"4");
//    painter.drawText((width()-40)-25+15,height()/2-25+35,"5");

//    painter.drawText(15+20,height()-70+35,"6");
//    painter.drawText((width()-40)/3-25+15,height()-70+35,"7");
//    painter.drawText((width()-40)/3*2-25+15,height()-70+35,"8");
//    painter.drawText((width()-40)-25+15,height()-70+35,"9");
}

void SSVEP::display(int frep)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    int i=current_frame;
    if(frep==0)
    {
        drawArrows(painter,width()/2,100,qRgb(gray_weight[i][0],gray_weight[i][0],gray_weight[i][0]),Up);
        drawArrows(painter,width()/2,height()-100,qRgb(gray_weight[i][1],gray_weight[i][1],gray_weight[i][1]),Down);
        drawArrows(painter,100,height()/2,qRgb(gray_weight[i][2],gray_weight[i][2],gray_weight[i][2]),Left);
        drawArrows(painter,width()-100,height()/2,qRgb(gray_weight[i][3],gray_weight[i][3],gray_weight[i][3]),Right);
    }
    else {
        drawArrows(painter,width()/2,100,qRgb(gray_weight[i][frep],gray_weight[i][frep],gray_weight[i][frep]),Up);
        drawArrows(painter,width()/2,height()-100,qRgb(gray_weight[i][frep],gray_weight[i][frep],gray_weight[i][frep]),Down);
        drawArrows(painter,100,height()/2,qRgb(gray_weight[i][frep],gray_weight[i][frep],gray_weight[i][frep]),Left);
        drawArrows(painter,width()-100,height()/2,qRgb(gray_weight[i][frep],gray_weight[i][frep],gray_weight[i][frep]),Right);
    }
//    //上四个方块
//    painter.fillRect(20,20,50,50,qRgb(gray_weight[i][0],gray_weight[i][0],gray_weight[i][0]));
//    painter.fillRect((width()-40)/3-25,20,50,50,qRgb(gray_weight[i][1],gray_weight[i][1],gray_weight[i][1]));
//    painter.fillRect((width()-40)/3*2-25,20,50,50,qRgb(gray_weight[i][2],gray_weight[i][2],gray_weight[i][2]));
//    painter.fillRect((width()-40)-25,20,50,50,qRgb(gray_weight[i][3],gray_weight[i][3],gray_weight[i][3]));
//    //中二个方块
//    painter.fillRect(20,height()/2-25,50,50,qRgb(gray_weight[i][4],gray_weight[i][4],gray_weight[i][4]));
//    painter.fillRect((width()-40)-25,height()/2-25,50,50,qRgb(gray_weight[i][5],gray_weight[i][5],gray_weight[i][5]));
//    //下四个方块
//    painter.fillRect(20,height()-70,50,50,qRgb(gray_weight[i][6],gray_weight[i][6],gray_weight[i][6]));
//    painter.fillRect((width()-40)/3-25,height()-70,50,50,qRgb(gray_weight[i][7],gray_weight[i][7],gray_weight[i][7]));
//    painter.fillRect((width()-40)/3*2-25,height()-70,50,50,qRgb(gray_weight[i][8],gray_weight[i][8],gray_weight[i][8]));
//    painter.fillRect((width()-40)-25,height()-70,50,50,qRgb(gray_weight[i][8],gray_weight[i][8],gray_weight[i][8]));

//    QFont font("Arial", 20);
//    painter.setFont(font);
//    painter.setPen(Qt::black);
//    painter.drawText(15+20,35+20,"0");
//    painter.drawText((width()-40)/3-25+15,20+35,"1");
//    painter.drawText((width()-40)/3*2-25+15,20+35,"2");
//    painter.drawText((width()-40)-25+15,35+20,"3");

//    painter.drawText(20+15,height()/2-25+35,"4");
//    painter.drawText((width()-40)-25+15,height()/2-25+35,"5");

//    painter.drawText(15+20,height()-70+35,"6");
//    painter.drawText((width()-40)/3-25+15,height()-70+35,"7");
//    painter.drawText((width()-40)/3*2-25+15,height()-70+35,"8");
//    painter.drawText((width()-40)-25+15,height()-70+35,"9");
    current_frame++;
}

void SSVEP::display(QPainter &painter,int i,int frep)
{
    if(frep==-1)
    {
        drawArrows(painter,width()/2,150,qRgb(gray_weight[0][i],gray_weight[0][i],gray_weight[0][i]),Up);
        drawArrows(painter,width()/2,height()-150,qRgb(gray_weight[3][i],gray_weight[3][i],gray_weight[3][i]),Down);
        drawArrows(painter,150,height()/2,qRgb(gray_weight[1][i],gray_weight[1][i],gray_weight[1][i]),Left);
        drawArrows(painter,width()-150,height()/2,qRgb(gray_weight[2][i],gray_weight[2][i],gray_weight[2][i]),Right);
    }
    else {
        drawArrows(painter,width()/2,150,qRgb(gray_weight[frep][i],gray_weight[frep][i],gray_weight[frep][i]),Up);
        drawArrows(painter,width()/2,height()-150,qRgb(gray_weight[frep][i],gray_weight[frep][i],gray_weight[frep][i]),Down);
        drawArrows(painter,150,height()/2,qRgb(gray_weight[frep][i],gray_weight[frep][i],gray_weight[frep][i]),Left);
        drawArrows(painter,width()-150,height()/2,qRgb(gray_weight[frep][i],gray_weight[frep][i],gray_weight[frep][i]),Right);
    }
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
        frame_num=display_time*refreshRate;
        for(int i=0;i<filcker_num;i++)
        {
            QList<quint8> frame_data;
            for(int j=0;j<frame_num;j++)
            {
                quint8 data=255*0.5*(1+sin(2*PI*filckerFrep[i].toDouble()*((j+1)/(refreshRate*1.0))+filckerPhi[i].toDouble()*PI));
                frame_data.append(data);
            }
            this->gray_weight.append(frame_data);
        }
    }
}

void SSVEP::initTimer()
{
    timer=new Timer;
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
}

void SSVEP::initMarks()
{
    marks.clear();
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            marks.append(i);
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(marks.begin(), marks.end(), g);
}

void SSVEP::initCommunication()
{
    communication=new Communication;
    connect(this,&SSVEP::markChanged,communication,&Communication::append);
}

void SSVEP::initFrames(quint8 type)
{
    frames.clear();
    quint16 frame_num=((config.display_time/1000)+1)*60;
    for(int i=0;i<frame_num;i++)
    {
        QPixmap pixmap(width(),height());
        pixmap.fill(Qt::black);
        QPainter painter(&pixmap);
        display(painter,i,type);
        frames.append(pixmap);
    }
}

void SSVEP::initFrames()
{
    frames.clear();
    quint16 frame_num=((config.display_time/1000))*60;
    for(int i=0;i<frame_num;i++)
    {
        QPixmap pixmap(width(),height());
        pixmap.fill(Qt::black);
        QPainter painter(&pixmap);
        display(painter,i);
//        pixmap.save(QString("%1.jpg").arg(i+1));
        frames.append(pixmap);
    }
}
void SSVEP::start_display()
{
    communication->connectAmplifier();
    type=true;
    print("第"+QString::number(current_task_num+1)+"次任务");
    if(mode)
    {
       initFrames(marks[current_task_num]);
       print("当前频率："+QString::number(config.filckerFrep[marks[current_task_num]].toFloat()));
       emit markChanged(marks[current_task_num]+1);
    }
    emit markChanged(4);
    start_time=QDateTime::currentMSecsSinceEpoch();
    timer->start(16);
}

void SSVEP::readInput()
{
     char chBuf[4096];
     DWORD dwRead;
     HANDLE hStdinDup;

     const HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
     if (hStdin == INVALID_HANDLE_VALUE)
         return;

     DuplicateHandle(GetCurrentProcess(), hStdin,
                     GetCurrentProcess(), &hStdinDup,
                     0, false, DUPLICATE_SAME_ACCESS);

     CloseHandle(hStdin);
     while (read_status) {
         bool ok = ReadFile(hStdinDup, chBuf, sizeof(chBuf), &dwRead, NULL);
         // emit sig_log(QLatin1String("ok is:")+QString::number(ok));
         if (ok && dwRead != 0)
         {
              emit newCommand(chBuf[0]);
         }
         QThread::usleep(10);
     }
}

void SSVEP::readCommand(quint8 command)
{
      if(command==0)
      {
          start_display();
      }
      if(command==1)
      {
          show();
      }
      if(command==2)
      {
          hide();
      }
}
