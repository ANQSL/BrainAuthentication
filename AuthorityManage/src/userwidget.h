#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include "userrolewidget.h"
#include "useraddwidget.h"
namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
    void appendUserInfo(QVariantList);
    void appendURInfo(QVariantList);
    void setURName(QString);
    void showURWidget();
signals:
    void passwordClicked(int);
    void roleClicked(int);
    void cancelClicked(int);
    void addUser(QStringList);
private slots:
    void on_add_user_clicked();

private:
    Ui::UserWidget *ui;
    UserRoleWidget *urwidget;
    UserAddWidget *uawidget;

};

#endif // USERWIDGET_H
