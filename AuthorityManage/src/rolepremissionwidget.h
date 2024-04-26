#ifndef ROLEPREMISSIONWIDGET_H
#define ROLEPREMISSIONWIDGET_H

#include <QWidget>
#include "rptablewidget.h"
namespace Ui {
class RolePremissionWidget;
}

class RolePremissionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RolePremissionWidget(QWidget *parent = nullptr);
    ~RolePremissionWidget();
    void append(QVariantList);
    void setName(QString);

private:
    Ui::RolePremissionWidget *ui;
};

#endif // ROLEPREMISSIONWIDGET_H
