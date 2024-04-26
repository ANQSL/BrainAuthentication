#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}
QString User::getName() const
{
    return name;
}
void User::setName(const QString &value)
{
    name = value;
}
QString User::getId() const
{
    return id;
}
void User::setId(const QString &value)
{
    id = value;
}

bool User::getStatus() const
{
    return status;
}
void User::setStatus(bool value)
{
    status = value;
}

QList<int> User::getPermissionLevel() const
{
    return permission_level;
}
void User::setPermissionLevel(const QList<int> &value)
{
    permission_level = value;
}
