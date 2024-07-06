#ifndef RECEIVECOMMANDTASK_H
#define RECEIVECOMMANDTASK_H

#include <QObject>
#include "QThread"
class ReceiveCommandTask : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveCommandTask(QObject *parent = nullptr);
    void start();
    void stop();
protected:
    void run() override;
signals:
    void newCommand(int);
private:
    bool status;
};

#endif // RECEIVECOMMANDTASK_H
