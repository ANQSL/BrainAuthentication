#ifndef SSVEP_H
#define SSVEP_H
#include "QWidget"
#include "ssvepconfig.h"
#include "QTimer"
#include "QPainter"
#include "QOpenGLWidget"
#include "timer.h"
#include "communication.h"
#include "QSocketNotifier"
#include "receivecommandtask.h"
class SSVEP:public QOpenGLWidget
{
    Q_OBJECT
public:
    SSVEP();
    ~SSVEP();
    enum Direction { Up, Down, Left, Right };
signals:
    void markChanged(quint8);
    void newCommand(quint8);
private:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void drawArrows(QPainter &painter,int x,int y,QColor,Direction );
    void print(QString);
    SSVEPConfig config;
    QList<QList<quint8>> gray_weight;
    void initWidget();
    quint16 frame_num;
    void display(int frep=0);
    void display(QPainter&,int i,int frep=-1);
    void initGrayWeight();
    bool type=false;
    int current_frame=0;
    Timer *timer;
    void initTimer();
    bool mode=true;//ture：采集模式，false:识别模式
    QList<quint8> marks;
    int current_task_num=0;//当前任务数
    void initMarks();

    quint64 start_time;

    Communication *communication;
    void initCommunication();

    void start_display();

    //进程通信
    ReceiveCommandTask *receivce_command_task;
    void initReceiveCommandTask();
    // 处理指令
    void readCommand(quint8);

    bool running_status=false;


};

#endif // SSVEP_H
