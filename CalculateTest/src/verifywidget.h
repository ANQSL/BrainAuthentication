#ifndef VERIFYWIDGET_H
#define VERIFYWIDGET_H

#include <QWidget>

namespace Ui {
class VerifyWidget;
}

class VerifyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VerifyWidget(QWidget *parent = nullptr);
    ~VerifyWidget();
signals:
    void VerifyMsg(int,int);
private slots:
    void on_confirm_clicked();

private:
    Ui::VerifyWidget *ui;
};

#endif // VERIFYWIDGET_H
