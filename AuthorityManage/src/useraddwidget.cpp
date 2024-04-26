#include "useraddwidget.h"
#include "ui_useraddwidget.h"
#include "QMessageBox"
UserAddWidget::UserAddWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserAddWidget)
{
    ui->setupUi(this);
}

UserAddWidget::~UserAddWidget()
{
    delete ui;
}

void UserAddWidget::on_confirm_clicked()
{
    if(ui->name->text().isEmpty())
    {
        QMessageBox::about(this,"消息提示","请输入名字");
        return;
    }
    if(ui->accout->text().isEmpty())
    {
        QMessageBox::about(this,"消息提示","请输入账号");
        return;
    }
    if(ui->password->text().isEmpty())
    {
        QMessageBox::about(this,"消息提示","密码不能为空");
        return;
    }
    if(ui->ssvep->text().isEmpty())
    {
        QMessageBox::about(this,"消息提示","ssvep不能为空");
        return;
    }
    QStringList data;
    QString name=ui->name->text();
    QString accout=ui->accout->text();
    QString password=ui->password->text();
    QString ssvep=ui->ssvep->text();
    data.append(name);
    data.append(accout);
    data.append(password);
    data.append(ssvep);
    this->hide();
    emit addUser(data);
}
