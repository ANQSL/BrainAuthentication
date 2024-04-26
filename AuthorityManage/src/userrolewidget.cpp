#include "userrolewidget.h"
#include "ui_userrolewidget.h"

UserRoleWidget::UserRoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserRoleWidget)
{
    ui->setupUi(this);
}

UserRoleWidget::~UserRoleWidget()
{
    delete ui;
}

void UserRoleWidget::setName(QString name)
{
    ui->name->setText(name);
}

void UserRoleWidget::appendURInfo(QVariantList info)
{
    ui->ur_list->clear();
    for(auto data:info)
    {
      ui->ur_list->append(data.toStringList());
    }

}
