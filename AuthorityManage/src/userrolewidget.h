#ifndef USERROLEWIDGET_H
#define USERROLEWIDGET_H

#include <QWidget>

namespace Ui {
class UserRoleWidget;
}

class UserRoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserRoleWidget(QWidget *parent = nullptr);
    ~UserRoleWidget();
    void setName(QString);
    void appendURInfo(QVariantList);

private:
    Ui::UserRoleWidget *ui;
};

#endif // USERROLEWIDGET_H
