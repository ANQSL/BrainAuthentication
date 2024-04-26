#include "connectwidget.h"
#include "ui_connectwidget.h"
#include "QSerialPortInfo"
ConnectWidget::ConnectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWidget)
{
    ui->setupUi(this);
    init();
}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

void ConnectWidget::init()
{
    //初始化波特率的选择
    QStringList baudrates={"9600","115200","460800"};
    ui->baudrate->addItems(baudrates);
    this->setWindowTitle("设备连接");
    this->setFixedSize(300,200);
}

void ConnectWidget::on_search_clicked()
{
   QList<QSerialPortInfo> infos=QSerialPortInfo::availablePorts();
   QStringList serial_name;
   for(auto info:infos)
   {
       QString name=info.portName();
       serial_name.append(name);
   }
   ui->serial->clear();
   ui->serial->addItems(serial_name);
}

void ConnectWidget::on_connect_clicked()
{
    QString serial_name=ui->serial->currentText();
    quint32 baudrate=ui->baudrate->currentText().toUInt();
    QMap<QString,QVariant> device_param;
    device_param["name"]=serial_name;
    device_param["baudrate"]=baudrate;
    emit connectDevice(device_param);
}

void ConnectWidget::setConnectStatus(QString status)
{
    ui->connect->setText(status);
}
