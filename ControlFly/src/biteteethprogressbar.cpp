#include "biteteethprogressbar.h"
#include "QPainter"
#include "QTimer"
BiteTeethProgressBar::BiteTeethProgressBar(QProgressBar *parent) : QProgressBar(parent)
{
    setMaximum(0);
    setMaximum(100);
    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,[=](){
        int _value=value();
        _value++;
        this->setValue(_value);
        if(_value==100)
        {
            timer->stop();
        }
    });
}

BiteTeethProgressBar::~BiteTeethProgressBar()
{
    delete timer;
}

void BiteTeethProgressBar::start()
{
    timer->start(30);
}
void BiteTeethProgressBar::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
       int width = this->width();
       int height = this->height();
       int segmentCount = 3;
       int intervalWidth = 2; // 间隔宽度
       int segmentWidth = (width - (segmentCount - 1) * intervalWidth) / segmentCount;

       QColor colors[5] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan};
       QColor intervalColor = Qt::black; // 间隔颜色

       // 绘制每段的填充部分
       for (int i = 0; i < segmentCount; ++i) {
           int valueRange = maximum() - minimum();
           int segmentValue = valueRange / segmentCount;
           int startValue = minimum() + i * segmentValue;
           int segmentStartX = i * (segmentWidth + intervalWidth);
           int progressWidth = (value() - startValue) * segmentWidth / segmentValue;

           // 绘制间隔
           if (i > 0) {
               painter.setBrush(intervalColor);
               painter.drawRect(segmentStartX - intervalWidth, 0, intervalWidth, height);
           }

           // 绘制段的填充部分
           if (value() > startValue) {
               int filledWidth = std::min(progressWidth, segmentWidth);
               painter.setBrush(colors[i]);
               painter.drawRect(segmentStartX, 0, filledWidth, height);
           }
       }
}
