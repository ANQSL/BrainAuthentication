#ifndef CHANNEL_SEL_DIALOG_H
#define CHANNEL_SEL_DIALOG_H

#include <QDialog>

namespace Ui {
class channel_sel_dialog;
}

class channel_sel_dialog : public QDialog
{
    Q_OBJECT//只有加上Q_OBJECT才可以使用信号与槽机制，一般都要在头文件派生类时加上它。

public:
    explicit channel_sel_dialog(QWidget *parent = 0);
    ~channel_sel_dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::channel_sel_dialog *ui;
    int channelFlag[16];
};

#endif // CHANNEL_SEL_DIALOG_H
