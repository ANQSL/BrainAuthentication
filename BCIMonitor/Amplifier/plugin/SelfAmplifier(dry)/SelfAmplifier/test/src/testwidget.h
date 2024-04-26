#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "selfamplifier.h"
#include "iirfilter.h"
namespace Ui {
class testWidget;
}

class testWidget : public QWidget
{
    Q_OBJECT

public:
    explicit testWidget(QWidget *parent = nullptr);
    ~testWidget();
    void timerEvent(QTimerEvent *event);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::testWidget *ui;
    SelfAmplifier amplifier;
    IIRFILTER filter;

};

#endif // TESTWIDGET_H
