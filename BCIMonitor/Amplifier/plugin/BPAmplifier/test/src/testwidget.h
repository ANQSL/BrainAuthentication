#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "bpamplifier.h"
namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = nullptr);
    ~TestWidget();

private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::TestWidget *ui;
    BPAmplifier *bpamplifier;
};

#endif // TESTWIDGET_H
