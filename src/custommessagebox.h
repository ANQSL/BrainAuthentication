#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QLabel>

class CustomMessageBox : public QObject
{
    Q_OBJECT
public:
    static void show(QWidget *parent,QString message);
signals:

private:
    static QLabel *label;
};

#endif // CUSTOMMESSAGEBOX_H
