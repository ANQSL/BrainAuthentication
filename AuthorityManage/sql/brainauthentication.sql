--
-- SQLiteStudio v3.4.4 生成的文件，周二 4月 9 15:50:50 2024
--
-- 所用的文本编码：System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- 表：permission
CREATE TABLE IF NOT EXISTS permission (level INTEGER UNIQUE PRIMARY KEY, info varchar (255) UNIQUE);

-- 表：role
CREATE TABLE IF NOT EXISTS role (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, name varchar (10) UNIQUE, info TEXT);
INSERT INTO role (id, name, info) VALUES (1, '管理员', '拥有全部权限');
INSERT INTO role (id, name, info) VALUES (2, '转向', '负责无人机转向');
INSERT INTO role (id, name, info) VALUES (3, '前进', '复制无人机前进');

-- 表：role_permission
CREATE TABLE IF NOT EXISTS role_permission (role_id INTEGER NOT NULL, permission_level INTEGER NOT NULL);
INSERT INTO role_permission (role_id, permission_level) VALUES (1, 1);
INSERT INTO role_permission (role_id, permission_level) VALUES (2, 2);
INSERT INTO role_permission (role_id, permission_level) VALUES (3, 3);

-- 表：user
CREATE TABLE IF NOT EXISTS user (account varchar (11) UNIQUE NOT NULL, password varchar (16) NOT NULL, ssvep varchar (255) UNIQUE NOT NULL, id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);
INSERT INTO user (account, password, ssvep, id) VALUES ('anqsl', '1235456', '456', 1);

-- 表：user_role
CREATE TABLE IF NOT EXISTS user_role (role_id INTEGER NOT NULL, user_id INTEGER NOT NULL);
INSERT INTO user_role (role_id, user_id) VALUES (1, 1);

-- 视图：user_account
CREATE VIEW IF NOT EXISTS user_account AS select account,password from user;

-- 视图：user_permission_view
CREATE VIEW IF NOT EXISTS user_permission_view AS select user.id,user_role.role_id,role_permission.permission_level from user join user_role on user.id=user_role.user_id join role_permission on role_permission.role_id=user_role.role_id;

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
