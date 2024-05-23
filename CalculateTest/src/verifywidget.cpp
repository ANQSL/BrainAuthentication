#include "verifywidget.h"
#include "ui_verifywidget.h"

VerifyWidget::VerifyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerifyWidget)
{
    ui->setupUi(this);
}

VerifyWidget::~VerifyWidget()
{
    delete ui;
}

void VerifyWidget::on_confirm_clicked()
{
    emit VerifyMsg(ui->ssvep_id->text().toUInt(),ui->recognition_id->text().toInt());
    hide();
}
