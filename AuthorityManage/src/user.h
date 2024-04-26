#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    QString getName() const;
    void setName(const QString &value);

    QString getId() const;
    void setId(const QString &value);

    bool getStatus() const;
    void setStatus(bool value);

    QList<int> getPermissionLevel() const;
    void setPermissionLevel(const QList<int> &value);

signals:
private:
    QString name;
    QString id;
    bool status;
    QList<int> permission_level;
};
#endif // USER_H
