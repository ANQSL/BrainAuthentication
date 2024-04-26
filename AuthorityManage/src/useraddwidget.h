#ifndef USERADDWIDGET_H
#define USERADDWIDGET_H

#include <QWidget>

namespace Ui {
class UserAddWidget;
}

class UserAddWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserAddWidget(QWidget *parent = nullptr);
    ~UserAddWidget();
signals:
    void addUser(QStringList);

private slots:
    void on_confirm_clicked();

private:
    Ui::UserAddWidget *ui;
};

#endif // USERADDWIDGET_H
