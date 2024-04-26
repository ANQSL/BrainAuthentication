#ifndef USERTABLEWIDGET_H
#define USERTABLEWIDGET_H

#include <QWidget>
#include "QPushButton"
#include "QHBoxLayout"
namespace Ui {
class UserTableWidget;
}
namespace  user{
    class SwitchButton;
    class OperationButton;
}
class user::OperationButton:public QWidget
{
    Q_OBJECT
public:
    OperationButton(QWidget *parent=nullptr);
    ~OperationButton();
    int getId() const;
    void setId(int value);

signals:
    void passwordClicked(int);
    void roleClicked(int);
    void cancelClicked(int);
private:
    QPushButton* password;
    QPushButton* role;
    QPushButton* cancel;
    QHBoxLayout* layout;
    int id;
};
class user::SwitchButton:public QWidget
{
public:
    SwitchButton(QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event)override;
    bool getStatus() const;
    void setStatus(bool value);

private:
    bool status;
};
class UserTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserTableWidget(QWidget *parent = nullptr);
    ~UserTableWidget();
    void append(QStringList);
    void clear();
signals:
    void passwordClicked(int);
    void roleClicked(int);
    void cancelClicked(int);
private:
    Ui::UserTableWidget *ui;
};

#endif // USERTABLEWIDGET_H
