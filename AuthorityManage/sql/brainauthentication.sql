--
-- SQLiteStudio v3.4.4 ���ɵ��ļ����ܶ� 4�� 9 15:50:50 2024
--
-- ���õ��ı����룺System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- ��permission
CREATE TABLE IF NOT EXISTS permission (level INTEGER UNIQUE PRIMARY KEY, info varchar (255) UNIQUE);

-- ��role
CREATE TABLE IF NOT EXISTS role (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, name varchar (10) UNIQUE, info TEXT);
INSERT INTO role (id, name, info) VALUES (1, '����Ա', 'ӵ��ȫ��Ȩ��');
INSERT INTO role (id, name, info) VALUES (2, 'ת��', '�������˻�ת��');
INSERT INTO role (id, name, info) VALUES (3, 'ǰ��', '�������˻�ǰ��');

-- ��role_permission
CREATE TABLE IF NOT EXISTS role_permission (role_id INTEGER NOT NULL, permission_level INTEGER NOT NULL);
INSERT INTO role_permission (role_id, permission_level) VALUES (1, 1);
INSERT INTO role_permission (role_id, permission_level) VALUES (2, 2);
INSERT INTO role_permission (role_id, permission_level) VALUES (3, 3);

-- ��user
CREATE TABLE IF NOT EXISTS user (account varchar (11) UNIQUE NOT NULL, password varchar (16) NOT NULL, ssvep varchar (255) UNIQUE NOT NULL, id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);
INSERT INTO user (account, password, ssvep, id) VALUES ('anqsl', '1235456', '456', 1);

-- ��user_role
CREATE TABLE IF NOT EXISTS user_role (role_id INTEGER NOT NULL, user_id INTEGER NOT NULL);
INSERT INTO user_role (role_id, user_id) VALUES (1, 1);

-- ��ͼ��user_account
CREATE VIEW IF NOT EXISTS user_account AS select account,password from user;

-- ��ͼ��user_permission_view
CREATE VIEW IF NOT EXISTS user_permission_view AS select user.id,user_role.role_id,role_permission.permission_level from user join user_role on user.id=user_role.user_id join role_permission on role_permission.role_id=user_role.role_id;

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
