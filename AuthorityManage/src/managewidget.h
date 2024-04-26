#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>

namespace Ui {
class ManageWidget;
}

class ManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManageWidget(QWidget *parent = nullptr);
    ~ManageWidget();
    void appendRoleInfo(QVariantList);
    void clearRoleInfo();
    void appendRPInfo(QVariantList);
    void setRPRoleName(QString);
    void showRPWidget();

    void appendUserInfo(QVariantList);
    void appendURInfo(QVariantList);
    void setURName(QString);
    void showURWidget();

signals:
    void currentRole();
    void checkRole(int);
    void currentUser();
    void roleClicked(int);
    void addUser(QStringList);
    void cancelUser(int);
private slots:
    void currentChangeSlot(int);
private:
    Ui::ManageWidget *ui;
    void setConnect();
};

#endif // MANAGEWIDGET_H
