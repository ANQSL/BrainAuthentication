#ifndef CALCULATETEST_H
#define CALCULATETEST_H

#include <QWidget>
#include "QChart"
#include "QChartView"
#include "verifywidget.h"
using namespace QtCharts;
namespace Ui {
class CalculateTest;
}

class CalculateTest : public QWidget
{
    Q_OBJECT

public:
    explicit CalculateTest(QWidget *parent = nullptr);
    ~CalculateTest();
    void appendSSVEP(int);
    void appendRecognition(int);

private slots:
    void on_reset_clicked();

private:
    Ui::CalculateTest *ui;

    int ssvep_id;
    int ssvep_num=0;
    int ssvep_correct=0;


    int recognition_id;
    int recognition_num=0;
    int recognition_correct=0;

    VerifyWidget verifywidget;
    void verify();
    //识别完成标志
    bool ssvep_status=false;
    bool recognition_status=false;
};

#endif // CALCULATETEST_H
