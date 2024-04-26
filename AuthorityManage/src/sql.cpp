#include "sql.h"
#include "QDir"
#include "QDebug"
#include "QSqlQuery"
#include "QSqlError"
SQL::SQL()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    QDir dir("data");
    bool isok=dir.exists();
    if(!isok)
    {
        dir.mkpath("data");

    }
    db.setDatabaseName("data/user.db");
    open();
    if(!isok)
    {
        initDataBase();
    }
}

bool SQL::open()
{
    return db.open();
}

void SQL::close()
{
    return db.close();
}

double *SQL::userSSVEP(QString)
{
    return NULL;
}

QList<int> SQL::userAuthorLevel(QString id)
{
    QList<int> level;
    QSqlQuery query;
    QString sql=QString("select permission_level from user_permission_view where user_id=%1").arg(id);
    if(query.exec(sql))
    {
        while (query.next()) {
            int level_ = query.value(0).toInt();
            level.append(level_);
        }
    }
    else
    {

    }
    return level;
}

QStringList SQL::userRole(QString)
{
    return {""};
}

QVariantList SQL::RoleInfo()
{
    QVariantList role_info;
    QSqlQuery query;
    QString sql=QString("select * from role_view");
    if(query.exec(sql))
    {
        while (query.next()) {
            QStringList role;
            QString id= query.value(0).toString();
            QString name= query.value(1).toString();
            QString info= query.value(2).toString();
            QString status= query.value(3).toString();
            role.append(id);
            role.append(name);
            role.append(info);
            role.append(status);
            role_info.append(role);
        }
    }
    else
    {

    }
    return role_info;
}

QVariantList SQL::PermissionInfo()
{
    QVariantList role_permission_info;
    QString sql="select *from permission";
    QSqlQuery query;
    if(query.exec(sql))
    {
        while (query.next()) {
            QStringList role;
            QString id= query.value(0).toString();
            QString level= query.value(1).toString();
            QString info= query.value(2).toString();
            role.append(id);
            role.append(role);
            role.append(info);
            role_permission_info.append(role);
        }
    }
    return role_permission_info;
}

QVariantList SQL::RolePermissionInfo(int role_id)
{
    QVariantList role_permission_info;
    QString sql="select *from permission";
    QSqlQuery query;
    if(query.exec(sql))
    {
        while (query.next()) {
            QStringList role;
            QString id= query.value(0).toString();
            QString level= query.value(1).toString();
            QString info= query.value(2).toString();
            role.append(id);
            role.append(level);
            role.append(info);
            QSqlQuery query;
            QString sql=QString("select * from role_permission_view where role_id=%1 and permission_id=%2").arg(role_id).arg(id);
            if(query.exec(sql))
            {
                  if(query.next())
                  {
                      role.append("1");
                  }
                  else
                  {
                      role.append("0");
                  }
            }
            role_permission_info.append(role);

        }
    }
    return role_permission_info;
}

QString SQL::roleName(int id)
{
    QString name;
    QString sql=QString("select  name from role where id=%1").arg(id);
    QSqlQuery query;
    if(query.exec(sql))
    {
        while (query.next()) {
            name= query.value(0).toString();
        }
    }
    return name;
}

QVariantList SQL::UserInfo()
{
    QVariantList user_info;
    QSqlQuery query;
    QString sql=QString("select * from user_view");
    if(query.exec(sql))
    {
        while (query.next()) {
            QStringList user;
            QString id= query.value(0).toString();
            QString account= query.value(1).toString();
            QString name= query.value(2).toString();
            QString status=query.value(5).toString();
            user.append(id);
            user.append(account);
            user.append(name);
            user.append(status);
            user_info.append(user);
        }
    }
    else
    {

    }
    return user_info;
}

QVariantList SQL::UserRoleInfo(int user_id)
{
    QVariantList user_role_info;
    QString sql="select *from role";
    QSqlQuery query;
    if(query.exec(sql))
    {
        while (query.next()) {
            QStringList user;
            QString id= query.value(0).toString();
            QString name= query.value(1).toString();
            QString info= query.value(2).toString();
            user.append(id);
            user.append(name);
            user.append(info);
            QSqlQuery query;
            QString sql=QString("select * from user_role_view where user_id=%1 and role_id=%2").arg(user_id).arg(id);
            if(query.exec(sql))
            {
                  if(query.next())
                  {
                      user.append("1");
                  }
                  else
                  {
                      user.append("0");
                  }
            }
            user_role_info.append(user);

        }
    }
    return user_role_info;
}

QString SQL::userName(int id)
{
    QString name;
    QString sql=QString("select  name from user where id=%1").arg(id);
    QSqlQuery query;
    if(query.exec(sql))
    {
        while (query.next()) {
            name= query.value(0).toString();
        }
    }
    return name;
}

bool SQL::addUser(QStringList data)
{
    QString name;
    QString sql=QString("insert into user('name','account','password','ssvep')values('%1','%2','%3','%4')")
            .arg(data[0]).arg(data[1]).arg(data[2]).arg(data[3]);
    QSqlQuery query;
    if(query.exec(sql))
    {
        QString sql="select id from role";
        QSqlQuery query;
        if(query.exec(sql))
        {
            QString sql=QString("select id from user where account='%1'").arg(data[1]);
            QSqlQuery query_user;
            query_user.exec(sql);
            query_user.next();
            QString user_id=query_user.value(0).toString();
            while (query.next()) {

                QString role_id=query.value(0).toString();
                QString sql=QString("insert into user_role(user_id,role_id)values(%1,%2)").arg(user_id).arg(role_id);
                QSqlQuery query_user_role;
                query_user_role.exec(sql);
            }
        }
        return true;
    }
    return false;
}

void SQL::cancelUser(int user_id)
{
    QString name;
    QString sql=QString("delete from user where id=%1").arg(user_id);
    QSqlQuery query;
    query.exec(sql);
    sql=QString("delete from user_role where user_id=%1").arg(user_id);
    query.exec(sql);
}
void SQL::initDataBase()
{
    QFile file("sql/brainauthentication.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open SQL file";
        return;
    }
    QTextStream in(&file);
    QSqlQuery query;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()&&!line.contains("--")) {
            qDebug()<<line;
            if (!query.exec(line)) {
                qDebug() << "Error executing SQL statement:" << query.lastError().text();
            }
        }
    }
    file.close();
}
