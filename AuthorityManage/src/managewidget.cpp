#include "managewidget.h"
#include "ui_managewidget.h"

ManageWidget::ManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageWidget)
{
    ui->setupUi(this);
    setConnect();
    ui->tabWidget->setTabText(0,"角色管理");
    ui->tabWidget->setTabText(1,"用户管理");
    ui->tabWidget->setCurrentIndex(0);
}

ManageWidget::~ManageWidget()
{
    delete ui;
}

void ManageWidget::appendRoleInfo(QVariantList info)
{
    ui->role->append(info);
}

void ManageWidget::clearRoleInfo()
{
    ui->role->clear();
}

void ManageWidget::appendRPInfo(QVariantList info)
{
    ui->role->appendRPInfo(info);
}

void ManageWidget::setRPRoleName(QString name)
{
    ui->role->setRPRoleName(name);
}
void ManageWidget::showRPWidget()
{
    ui->role->showRPWidget();
}

void ManageWidget::appendUserInfo(QVariantList user_info)
{
    ui->user->appendUserInfo(user_info);
}

void ManageWidget::appendURInfo(QVariantList info)
{
    ui->user->appendURInfo(info);
}

void ManageWidget::setURName(QString name)
{
    ui->user->setURName(name);
}

void ManageWidget::showURWidget()
{
    ui->user->showURWidget();
}

void ManageWidget::currentChangeSlot(int index)
{
    if(index==0)
    {
        emit currentRole();
    }
    else
    {
        emit currentUser();
    }
}

void ManageWidget::setConnect()
{
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&ManageWidget::currentChangeSlot);
    connect(ui->role,&RoleWidget::checkRole,this,&ManageWidget::checkRole); 
    connect(ui->user,&UserWidget::roleClicked,this,&ManageWidget::roleClicked);
    connect(ui->user,&UserWidget::addUser,this,&ManageWidget::addUser);
    connect(ui->user,&UserWidget::cancelClicked,this,&ManageWidget::cancelUser);

}
