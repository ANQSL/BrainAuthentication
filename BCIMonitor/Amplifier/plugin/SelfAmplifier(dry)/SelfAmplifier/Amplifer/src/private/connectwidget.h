#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include "QMap"
namespace Ui {
class ConnectWidget;
}

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent = nullptr);
    ~ConnectWidget();
public slots:
    void setConnectStatus(QString);
private slots:
    void on_search_clicked();

    void on_connect_clicked();
signals:
    void connectDevice(QMap<QString,QVariant>);
private:
    Ui::ConnectWidget *ui;
    void init();
};

#endif // CONNECTWIDGET_H
