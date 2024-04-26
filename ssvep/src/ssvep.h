#ifndef SSVEP_H
#define SSVEP_H
#include "QWidget"
#include "ssvepconfig.h"
#include "QTimer"
class SSVEP:public QWidget
{
    Q_OBJECT
public:
    SSVEP();
    ~SSVEP();
    enum Direction { Up, Down, Left, Right };
signals:
    void markChanged(int);
private:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void drawArrows(QPainter &painter,int x,int y,QColor,Direction );
    SSVEPConfig config;
    QList<QList<quint8>> gray_weight;
    void initWidget();
    void display(int frep=0);
    void initGrayWeight();
    bool type=false;
    int current_frame=0;
    QTimer *timer;
    void initTimer();
    bool mode;//ture：采集模式，false:识别模式
    QList<quint8> marks;
    int current_task_num=0;//当前任务数
    void initMarks();
};

#endif // SSVEP_H
