#include "testwidget.h"
#include "ui_testwidget.h"
#include "QDebug"
TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
    bpamplifier=new BPAmplifier;
}

TestWidget::~TestWidget()
{
    delete ui;
}


void TestWidget::on_pushButton_clicked()
{
    bpamplifier->start();
}

void TestWidget::on_pushButton_2_clicked()
{
    bpamplifier->stop();
}

void TestWidget::on_pushButton_3_clicked()
{
    bpamplifier->getConnectWidget()->show();
}

void TestWidget::on_pushButton_4_clicked()
{
    QList<QList<double>> data=bpamplifier->getArrayData();
    qDebug()<<data;
}

void TestWidget::on_pushButton_5_clicked()
{
    qDebug()<<bpamplifier->connectStatus();
}
