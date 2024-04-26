#include "usertablewidget.h"
#include "ui_usertablewidget.h"
#include "QPainter"
#include "QPushButton"
using namespace user;
UserTableWidget::UserTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTableWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "用户账号" << "角色名字" << "角色状态"<<"操作");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setShowGrid(false);
}

UserTableWidget::~UserTableWidget()
{
    delete ui;
}

void UserTableWidget::append(QStringList info)
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
    connect(operationbutton,&OperationButton::passwordClicked,this,&UserTableWidget::passwordClicked);
    connect(operationbutton,&OperationButton::roleClicked,this,&UserTableWidget::roleClicked);
    connect(operationbutton,&OperationButton::cancelClicked,this,&UserTableWidget::cancelClicked);
    ui->tableWidget->setCellWidget(row,3,operationbutton);
}

void UserTableWidget::clear()
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

OperationButton::OperationButton(QWidget *parent ):QWidget(parent)
{
    password=new QPushButton;
    password->setText("修改密码");
    role=new QPushButton;
    role->setText("用户角色");
    cancel=new QPushButton;
    cancel->setText("删除");
    layout=new QHBoxLayout;
    layout->addWidget(password);
    layout->addWidget(role);
    layout->addWidget(cancel);
    layout->setMargin(0);
    this->setLayout(layout);
    connect(password,&QPushButton::clicked,this,[=](){
        emit passwordClicked(id);
    });
    connect(role,&QPushButton::clicked,this,[=](){
        emit roleClicked(id);
    });
    connect(cancel,&QPushButton::clicked,this,[=](){
         emit cancelClicked(id);
    });
}
OperationButton::~OperationButton()
{
    delete password;
    delete role;
    delete cancel;
    delete layout;
}

int OperationButton::getId() const
{
    return id;
}

void OperationButton::setId(int value)
{
    id = value;
}
