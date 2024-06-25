#include "authoritymanage.h"
AuthorityManage::AuthorityManage(QObject *parent):QObject(parent)
{
    setConnect();
    initRoleInfo();
}

QList<int> AuthorityManage::userPressmission(int id)
{
    return sql.userPressmission(id);
}

void AuthorityManage::setConnect()
{
    connect(&widget,&ManageWidget::currentRole,this,&AuthorityManage::initRoleInfo);
    connect(&widget,&ManageWidget::checkRole,this,&AuthorityManage::checkRole);
    connect(&widget,&ManageWidget::currentUser,this,&AuthorityManage::initUserInfo);
    connect(&widget,&ManageWidget::roleClicked,this,&AuthorityManage::roleClicked);
    connect(&widget,&ManageWidget::addUser,this,&AuthorityManage::addUser);
    connect(&widget,&ManageWidget::cancelUser,this,&AuthorityManage::cancelUser);
}

void AuthorityManage::initRoleInfo()
{
     QVariantList role_info=sql.RoleInfo();
     widget.clearRoleInfo();
     widget.appendRoleInfo(role_info);
}

void AuthorityManage::checkRole(int role_id)
{
    QString name=sql.roleName(role_id);
    widget.setRPRoleName(name);
    QVariantList role_permission_info=sql.RolePermissionInfo(role_id);
    widget.appendRPInfo(role_permission_info);
    widget.showRPWidget();
}

void AuthorityManage::initUserInfo()
{
    QVariantList user_info=sql.UserInfo();
    widget.appendUserInfo(user_info);
}

void AuthorityManage::roleClicked(int user_id)
{
    QString name=sql.userName(user_id);
    widget.setURName(name);
    QVariantList user_role_info=sql.UserRoleInfo(user_id);
    widget.appendURInfo(user_role_info);
    widget.showURWidget();

}

void AuthorityManage::addUser(QStringList user_data)
{
    sql.addUser(user_data);
    initUserInfo();
}

void AuthorityManage::cancelUser(int user_id)
{
    sql.cancelUser(user_id);
    initUserInfo();
}
