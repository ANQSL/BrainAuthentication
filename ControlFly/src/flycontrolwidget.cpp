#include "flycontrolwidget.h"
#include "ui_flycontrolwidget.h"

FlyControlWidget::FlyControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlyControlWidget)
{
    ui->setupUi(this);
    bite_teeth_progressbar=new BiteTeethProgressBar;
    bite_teeth_progressbar->setParent(ui->fly_video);
    bite_teeth_progressbar->setGeometry(width()/2-100,5,200,10);
    current_command=new QLabel;
    current_command->setParent(ui->fly_video);
    current_command->setGeometry(width()/2-50,15,100,30);
    current_command->setAttribute(Qt::WA_TranslucentBackground);
    current_command->setAlignment(Qt::AlignHCenter);
    current_command->setText("当前指令");

    battery = new QLabel;
    battery->setParent(ui->fly_video);
    battery->setGeometry(width()- 200, 15, 200, 30);
    battery->setAttribute(Qt::WA_TranslucentBackground);
    battery->setAlignment(Qt::AlignRight);
    battery->setText("当前电量:100%  ");
}

FlyControlWidget::~FlyControlWidget()
{
    delete ui;
    delete bite_teeth_progressbar;
    delete current_command;
}

void FlyControlWidget::startControl()
{
    bite_teeth_progressbar->setValue(0);
    bite_teeth_progressbar->start();
}

void FlyControlWidget::resizeEvent(QResizeEvent *event)
{
    bite_teeth_progressbar->setGeometry(width()/2-100,5,200,10);
    current_command->setGeometry(width()/2-50,15,100,30);
    battery->setGeometry(width() - 200, 15, 200, 30);
}

void FlyControlWidget::setVideoFrame(QImage img)
{
    QPixmap pixmap=QPixmap::fromImage(img);
    ui->fly_video->setPixmap(pixmap);
}

void FlyControlWidget::setCurrentCommand(QString command)
{
    current_command->setText(command);
}
void FlyControlWidget::setBttery(quint8 value)
{
    battery->setText("当前电量："+QString::number(value)+"%");
}