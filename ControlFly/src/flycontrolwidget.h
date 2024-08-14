#ifndef FLYCONTROLWIDGET_H
#define FLYCONTROLWIDGET_H

#include <QWidget>
#include "biteteethprogressbar.h"
#include "QLabel"
namespace Ui {
class FlyControlWidget;
}

class FlyControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlyControlWidget(QWidget *parent = nullptr);
    ~FlyControlWidget();
    void startControl();
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void setVideoFrame(QImage);
    void setCurrentCommand(QString);
    void setBttery(quint8);
private:
    Ui::FlyControlWidget *ui;
    BiteTeethProgressBar *bite_teeth_progressbar;
    QLabel *current_command;
    QLabel* battery;
};

#endif // FLYCONTROLWIDGET_H
