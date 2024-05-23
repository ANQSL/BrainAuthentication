#include "calculatetest.h"
#include "ui_calculatetest.h"
#include "QDebug"
CalculateTest::CalculateTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculateTest)
{
    ui->setupUi(this);
    connect(&verifywidget,&VerifyWidget::VerifyMsg,this,[=](int ssvep_id, int recognition_id){
         ssvep_num++;
         recognition_num++;
         if(this->ssvep_id==ssvep_id)
         {
             ssvep_correct++;
         }
         if(this->recognition_id==recognition_id)
         {
             recognition_correct++;
         }
         ui->ssvep_num->setText(QString::number(ssvep_num));
         ui->ssvep_correct->setText(QString::number(ssvep_correct));
         ui->ssvep_acc->setText(QString::number(ssvep_correct*1.0/ssvep_num*100));
         ui->recognition_num->setText(QString::number(recognition_num));
         ui->recognition_correct->setText(QString::number(recognition_correct));
         ui->recognition_acc->setText(QString::number(recognition_correct*1.0/recognition_num*100));

         recognition_status=false;
         ssvep_status=false;
    });
}

CalculateTest::~CalculateTest()
{
    delete ui;
}

void CalculateTest::appendSSVEP(int id)
{
     qDebug()<<"ssvepid"<<id;
    ssvep_id=id;
    ssvep_status=true;
    if(recognition_status)
    {
        verify();
    }
}

void CalculateTest::appendRecognition(int id)
{
    qDebug()<<"识别id"<<id;
   recognition_id=id;
   recognition_status=true;
   if(ssvep_status)
   {
       verify();
   }
}

void CalculateTest::verify()
{
    verifywidget.show();
}

void CalculateTest::on_reset_clicked()
{
    ssvep_num=0;
    ssvep_correct=0;
    recognition_num=0;
    recognition_correct=0;
}
