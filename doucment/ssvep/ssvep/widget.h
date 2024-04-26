#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <stdio.h>
#include <stdlib.h>
#include "channel_sel_dialog.h"
#include "collectdatathread.h"
#include "ssveptestthread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;
    QTimer *timer6;
    //double **test;
    collectdatathread *threadData_test;
    ssveptestthread *threadSSVEPTest;


public slots:
    void Timer1timeout();
    void Timer2timeout();
    void Timer3timeout();
    void Timer4timeout();
    void Timer5timeout();
    void Timer6timeout();



private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    //void logCCAVal(int val);
private:
    Ui::Widget *ui;
    int num_time1;
    int num_time2;
    int num_time3;
    int num_time4;
    int num_time5;
    int num_time6;
    FILE **EEG;


};

#endif // WIDGET_H
