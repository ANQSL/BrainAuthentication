#include "rolepremissionwidget.h"
#include "ui_rolepremissionwidget.h"

RolePremissionWidget::RolePremissionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RolePremissionWidget)
{
    ui->setupUi(this);
}

RolePremissionWidget::~RolePremissionWidget()
{
    delete ui;
}

void RolePremissionWidget::append(QVariantList info)
{
    ui->p_list->clear();
    for(auto data:info)
    {
        ui->p_list->append(data.toStringList());
    }
}

void RolePremissionWidget::setName(QString name)
{
    ui->name->setText(name);
}
