#ifndef URTABLEWIDGET_H
#define URTABLEWIDGET_H

#include <QWidget>
#include "QHeaderView"
namespace Ui {
class URTableWidget;
}
namespace UR {
class HeadView;
}
class UR::HeadView: public QHeaderView
{
    Q_OBJECT
public:
    HeadView(Qt::Orientation orientation, QWidget * parent = 0);
    void cancelSelectAll();
signals:
    void signalStateTrange(int);
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex)const;
    void mousePressEvent(QMouseEvent *event);
private:
    bool isOn;
};
class URTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit URTableWidget(QWidget *parent = nullptr);
    ~URTableWidget();
    void append(QStringList info);
    void clear();
private:
    Ui::URTableWidget *ui;
    UR::HeadView *headview;
};

#endif // URTABLEWIDGET_H
