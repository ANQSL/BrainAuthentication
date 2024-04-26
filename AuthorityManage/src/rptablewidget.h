#ifndef RPTABLEWIDGET_H
#define RPTABLEWIDGET_H

#include <QWidget>
#include "QHeaderView"
namespace Ui {
class RPTableWidget;
}
namespace RP{
    class HeadView;
}
class RP::HeadView: public QHeaderView
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
class RPTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RPTableWidget(QWidget *parent = nullptr);
    ~RPTableWidget();
    void append(QStringList info);
    void clear();
private:
    Ui::RPTableWidget *ui;
    RP::HeadView *headview;
};

#endif // RPTABLEWIDGET_H
