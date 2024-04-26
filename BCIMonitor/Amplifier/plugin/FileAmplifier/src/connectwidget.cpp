#include "connectwidget.h"
#include "ui_connectwidget.h"
#include "QFileDialog"
ConnectWidget::ConnectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);
    this->status=false;
}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

void ConnectWidget::setConnectStatus(QString status)
{
    ui->connect->setText(status);
}

void ConnectWidget::on_search_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"文件选择","eegdata");
    ui->path->setText(path);
}

void ConnectWidget::on_connect_clicked()
{
    if(status)
    {
       this->status=false;
       emit closeDevice();
    }
    else
    {
        QString path=ui->path->text();
        if(!path.isEmpty())
        {
            this->status=true;
            emit connectDevice(path);
        }
    }


}
