#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QLabel>
#include "QVBoxLayout"
class CustomMessageBox : public QObject
{
    Q_OBJECT
public:
    static void show(QWidget *parent,QString message);
    static void show(QWidget *parent,QString message,QString photo);
signals:

private:
    static QLabel *label;
    static QLabel *Photo;
    static QWidget *widget;
};

#endif // CUSTOMMESSAGEBOX_H
