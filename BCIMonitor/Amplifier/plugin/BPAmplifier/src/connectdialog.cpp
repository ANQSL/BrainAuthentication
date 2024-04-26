#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "QMessageBox"
#include "QDebug"
#include "QMovie"
ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("设备连接");
    loading=new QLabel(this);
    loading->resize(this->size()/2);
    loading->raise();
    QMovie *movie=new QMovie(":/BPAmplifier/image/loading.gif");
    movie->start();
    loading->setMovie(movie);
    loading->setScaledContents(true);
    loading->hide();
    loading->move(this->width()/4,this->height()/4);
    this->ui->device->setEnabled(false);
    this->ui->connect->setEnabled(false);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::setFamily(QStringList value)
{
    ui->family->clear();
    this->ui->family->addItems(value);
}

void ConnectDialog::setType(QStringList value)
{
    ui->type->clear();
    ui->type->addItems(value);
}

void ConnectDialog::setDeviceNum(int num)
{
    ui->device->clear();
    this->ui->device->setEnabled(true);
    this->ui->search->setEnabled(true);
    if(num==0)
    {
        loading->hide();
        return;
    }
    for(int i=0;i<num;i++)
    {
        ui->device->addItem(QString::number(i));
    }

    this->ui->connect->setEnabled(true);
    loading->hide();
}

void ConnectDialog::showError(QString error)
{
    QMessageBox::about(this,"连接信息",error);
}
void ConnectDialog::setStatus(bool status)
{
    ui->type->setEnabled(!status);
    ui->device->setEnabled(!status);
    ui->device->setEnabled(!status);
    ui->search->setEnabled(!status);
    ui->connect->setEnabled(status);
    if(status)
    {
        ui->connect->setText("断开");
    }
    else
    {
        ui->connect->setText("连接");
    }
}
void ConnectDialog::on_connect_clicked()
{
    emit connect(ui->device->currentIndex());
}

void ConnectDialog::on_search_clicked()
{
    loading->show();
    this->ui->search->setEnabled(false);
    emit search();
}

void ConnectDialog::on_family_currentIndexChanged(int index)
{
    emit familyChanged(index);
}

void ConnectDialog::on_type_currentIndexChanged(int index)
{
    emit typeChanged(index);
}
