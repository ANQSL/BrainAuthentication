#include "urtablewidget.h"
#include "ui_urtablewidget.h"
#include "QCheckBox"
#include "QPainter"
#include "QMouseEvent"
using namespace UR;
URTableWidget::URTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::URTableWidget)
{
    ui->setupUi(this);
    headview=new HeadView(Qt::Horizontal,ui->tableWidget);
    ui->tableWidget->setHorizontalHeader(headview);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<" "<<"角色名字" << "角色说明");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

URTableWidget::~URTableWidget()
{
    delete ui;
}

void URTableWidget::append(QStringList info)
{
    int row=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QCheckBox *box=new QCheckBox;
    box->setChecked(info[3].toUInt());
    ui->tableWidget->setCellWidget(row,0,box);
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(info[1]));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(info[2]));
}

void URTableWidget::clear()
{
    while (ui->tableWidget->rowCount() > 0) {
        ui->tableWidget->removeRow(0);
    }
}

HeadView::HeadView(Qt::Orientation orientation, QWidget *parent):QHeaderView(orientation,parent)
{

}
void UR::HeadView::cancelSelectAll()
{
    isOn = false;
    emit signalStateTrange(isOn);
    this->update();
}

void UR::HeadView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (logicalIndex == 0)
    {
        QStyleOptionButton option;
        option.rect = QRect(10, 10, 10, 10);
        if (isOn)
            option.state = QStyle::State_On;
        else
            option.state = QStyle::State_Off;
        QCheckBox checkBox;
        option.iconSize = QSize(20, 20);
        option.rect = rect;
        style()->drawControl(QStyle::CE_CheckBox, &option, painter, &checkBox);
    }
}

void UR::HeadView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int index = logicalIndexAt(event->pos());
        if (index == 0)
        {
            if (isOn)
                isOn = false;
            else
                isOn = true;
        }
        emit signalStateTrange(isOn);
    }
    this->update();
    QHeaderView::mousePressEvent(event);
}
