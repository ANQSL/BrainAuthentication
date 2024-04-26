#ifndef ROLEWIDGET_H
#define ROLEWIDGET_H

#include <QWidget>
#include "rolepremissionwidget.h"
namespace Ui {
class RoleWidget;
}

class RoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoleWidget(QWidget *parent = nullptr);
    ~RoleWidget();
    void append(QVariantList role_data);
    void appendRPInfo(QVariantList role_permission_info);
    void clear();
    void setRPRoleName(QString);
    void showRPWidget();
signals:
    void checkRole(int);
private:
    Ui::RoleWidget *ui;
    RolePremissionWidget *rpwidget;
    void initRPWidget();
};

#endif // ROLEWIDGET_H
