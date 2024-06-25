#include "custommessagebox.h"
#include "QTimer"
QLabel * CustomMessageBox::label=NULL;
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
