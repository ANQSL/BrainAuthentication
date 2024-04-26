#include "tablewidget.h"
#include "ui_tablewidget.h"
#include "ui_operationbutton.h"
#include "QCheckBox"
#include "QRadioButton"
#include "QHBoxLayout"
#include "QPainter"
using namespace Role;
TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "角色名字" << "角色描述" << "角色状态"<<"操作");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setShowGrid(false);
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::append(QStringList info)
{

    int row=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(info[1]));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(info[2]));
    SwitchButton *switchbutton=new SwitchButton;
    switchbutton->setStatus(info[3].toInt());
    ui->tableWidget->setCellWidget(row,2,switchbutton);
    OperationButton *operationbutton=new OperationButton();
    operationbutton->setId(info[0].toInt());
    connect(operationbutton,&OperationButton::checked,this,&TableWidget::checkRole);
    connect(operationbutton,&OperationButton::cancaled,this,&TableWidget::cancaled);
    ui->tableWidget->setCellWidget(row,3,operationbutton);
}

void TableWidget::clear()
{
    while (ui->tableWidget->rowCount() > 0) {
        ui->tableWidget->removeRow(0);
    }
}

SwitchButton::SwitchButton(QWidget *parent):QWidget(parent),status(false)
{

}

void SwitchButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 绘制按钮背景
    painter.setBrush(status ? Qt::green : Qt::red);
    painter.drawRect(0, 0, width(), height());
    // 绘制按钮上的文本
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, status ? "ON" : "OFF");
}
void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    status = !status;
    update();
}
bool SwitchButton::getStatus() const
{
    return status;
}

void SwitchButton::setStatus(bool value)
{
    status = value;
}

OperationButton::OperationButton(QWidget *parent):QWidget(parent),ui(new Ui::OperationButton)
{
    ui->setupUi(this);
}

OperationButton::~OperationButton()
{
    delete ui;
}

void OperationButton::setId(int id)
{
    this->id=id;
}

void OperationButton::on_cancal_clicked()
{
    emit cancaled();
}

void OperationButton::on_permission_clicked()
{
    emit checked(id);
}
