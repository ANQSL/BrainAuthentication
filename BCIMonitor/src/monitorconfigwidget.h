#ifndef MONITORCONFIGWIDGET_H
#define MONITORCONFIGWIDGET_H

#include <QDialog>
#include "QProxyStyle"
#include "QTabWidget"
namespace Ui {
class MonitorConfigWidget;
}

class MonitorConfigWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorConfigWidget(QDialog *parent = nullptr);
    ~MonitorConfigWidget();
    void addConfigWidget(QWidget *,QString name);

private:
    Ui::MonitorConfigWidget *ui;
    QTabWidget *tabwidget;
};
class CustomTabStyle:public QProxyStyle{
public:
    CustomTabStyle(){}
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
};
#endif // MONITORCONFIGWIDGET_H
