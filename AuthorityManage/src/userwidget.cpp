#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget),urwidget(new UserRoleWidget),uawidget(new UserAddWidget)
{
    ui->setupUi(this);
    connect(ui->user_list,&UserTableWidget::passwordClicked,this,&UserWidget::passwordClicked);
    connect(ui->user_list,&UserTableWidget::roleClicked,this,&UserWidget::roleClicked);
    connect(ui->user_list,&UserTableWidget::cancelClicked,this,&UserWidget::cancelClicked);
    connect(uawidget,&UserAddWidget::addUser,this,&UserWidget::addUser);
}

UserWidget::~UserWidget()
{
    delete ui;
    delete urwidget;
    delete uawidget;
}

void UserWidget::appendUserInfo(QVariantList user_info)
{
    ui->user_list->clear();
    for(auto data:user_info)
    {
        QStringList user=data.toStringList();
        ui->user_list->append(user);
    }
}

void UserWidget::appendURInfo(QVariantList info)
{
    urwidget->appendURInfo(info);
}

void UserWidget::setURName(QString name)
{
    urwidget->setName(name);
}

void UserWidget::showURWidget()
{
    urwidget->show();
}

void UserWidget::on_add_user_clicked()
{
    uawidget->show();
}
