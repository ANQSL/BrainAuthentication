#ifndef AUTHORITYMANAGE_H
#define AUTHORITYMANAGE_H
#include "managewidget.h"
#include "sql.h"
#include "user.h"
class  AuthorityManage:public QObject
{
    Q_OBJECT
public:
    explicit AuthorityManage(QObject *parent=nullptr);
    QList<int> userPressmission(int);
    QString getUserName(int);
    QStringList getUserInfo(int);
signals:
private:
    void setConnect();
    ManageWidget widget;
    SQL sql;
    void initRoleInfo();
    void checkRole(int);

    void initUserInfo();
    void roleClicked(int);

    void addUser(QStringList);
    void cancelUser(int);
};

#endif // AUTHORITYMANAGE_H
