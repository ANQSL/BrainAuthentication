#ifndef BITETEETHPROGRESSBAR_H
#define BITETEETHPROGRESSBAR_H

#include <QObject>
#include "QProgressBar"
class BiteTeethProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit BiteTeethProgressBar(QProgressBar *parent = nullptr);
    ~BiteTeethProgressBar();
    void start();
signals:
protected:
    void paintEvent(QPaintEvent *) override;
    QTimer *timer;
};

#endif // BITETEETHPROGRESSBAR_H
