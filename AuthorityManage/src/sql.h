#ifndef SQL_H
#define SQL_H
#include "QSqlDatabase"
#include "QList"
#include "QVariantList"
class SQL
{
public:
    SQL();
    bool open();
    void close();
    double *userSSVEP(QString);
    QList<int> userAuthorLevel(QString);
    QStringList userRole(QString);
    //权限
    QVariantList PermissionInfo();
    //角色
    QVariantList RoleInfo();
    QVariantList RolePermissionInfo(int role_id);
    QString roleName(int id);
    //用户
    QVariantList UserInfo();
    QVariantList UserRoleInfo(int user_id);
    QString userName(int id);
    bool addUser(QStringList);
    void cancelUser(int);

private:
    QSqlDatabase db;
    void initDataBase();
};

#endif // SQL_H
