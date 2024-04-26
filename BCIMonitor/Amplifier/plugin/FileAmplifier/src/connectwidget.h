#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>

namespace Ui {
class ConnectWidget;
}

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent = nullptr);
    ~ConnectWidget();
    void setConnectStatus(QString);
private slots:
    void on_search_clicked();

    void on_connect_clicked();
signals:
    void connectDevice(QString);
    void closeDevice();
private:
    Ui::ConnectWidget *ui;
    bool status;
};

#endif // CONNECTWIDGET_H
