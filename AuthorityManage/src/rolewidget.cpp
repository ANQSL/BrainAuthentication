#include "rolewidget.h"
#include "ui_rolewidget.h"
#include "QDebug"
RoleWidget::RoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoleWidget)
{
    ui->setupUi(this);
    initRPWidget();
    connect(ui->role_list,&TableWidget::checkRole,this,&RoleWidget::checkRole);
}

RoleWidget::~RoleWidget()
{
    delete ui;
}

void RoleWidget::append(QVariantList role_data)
{
    for(auto data:role_data)
    {
        QStringList role_info=data.toStringList();
        ui->role_list->append(role_info);

    }
}

void RoleWidget::appendRPInfo(QVariantList role_permission_info)
{
    rpwidget->append(role_permission_info);
}

void RoleWidget::clear()
{
    ui->role_list->clear();
}

void RoleWidget::setRPRoleName(QString name)
{
    rpwidget->setName(name);
}

void RoleWidget::showRPWidget()
{
    rpwidget->show();
}

void RoleWidget::initRPWidget()
{
    rpwidget=new RolePremissionWidget;
}
