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
private:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    SSVEPConfig config;
    QList<QList<quint8>> gray_weight;
    void initWidget();
    void display();
    void initGrayWeight();
    bool type=false;
    int current_frame=0;
    QTimer *timer;
    void initTimer();
};

#endif // SSVEP_H
