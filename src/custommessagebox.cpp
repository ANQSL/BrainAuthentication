#include "custommessagebox.h"
#include "QTimer"
QLabel * CustomMessageBox::label=NULL;
QLabel * CustomMessageBox::Photo=NULL;
QWidget * CustomMessageBox::widget=NULL;
void CustomMessageBox::show(QWidget *parent, QString message)
{
    label=new QLabel;
    label->setFixedSize(800,150);
    label->setParent(parent);
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(30);
    label->setFont(font);
    label->setStyleSheet("color:white;");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setWindowFlag(Qt::FramelessWindowHint);
    label->show();
    QTimer::singleShot(1000,[=](){
        label->hide();
        delete label;
    });
}
void CustomMessageBox::show(QWidget *parent, QString message,QString photo)
{
    widget=new QWidget(parent);
    widget->setFixedSize(200,350);
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setWindowFlag(Qt::FramelessWindowHint);
    label=new QLabel;
    Photo=new QLabel;
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(Photo,4,Qt::AlignCenter);
    layout->addWidget(label,1,Qt::AlignCenter);
    widget->setLayout(layout);
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(30);
    label->setFont(font);
    label->setStyleSheet("color:white;");
    label->setAttribute(Qt::WA_TranslucentBackground);
    QPixmap pixmap;
    pixmap.load(photo);
    Photo->setPixmap(pixmap);
    widget->show();
//    widget->move((parent->width() - widget->width())/2,(parent->height() - widget->height())/2);
    QTimer::singleShot(1500,[=](){
        widget->hide();
        delete label;
        delete layout;
        delete Photo;
        delete widget;
    });
}
