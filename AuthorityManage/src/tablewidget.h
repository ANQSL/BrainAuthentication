#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
namespace Ui {
    class TableWidget;
    class OperationButton;
}
namespace Role {
    class OperationButton;
}
class Role::OperationButton:public QWidget
{
    Q_OBJECT
public:
    explicit  OperationButton(QWidget*parent=nullptr);
    ~OperationButton();
    void setId(int);
private slots:
    void on_cancal_clicked();
    void on_permission_clicked();
signals:
    void cancaled();
    void checked(int);
private:
    Ui::OperationButton *ui;
    int id;
};
class SwitchButton:public QWidget
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
class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget();
    void append(QStringList);
    void clear();
signals:
    void checkRole(int);
    void cancaled();
private:
    Ui::TableWidget *ui;
};

#endif // TABLEWIDGET_H
