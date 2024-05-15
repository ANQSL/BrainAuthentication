#ifndef SSVEPWIDGET_H
#define SSVEPWIDGET_H

#include <QWidget>
#include "QProcess"
#include "Windows.h"
class SSVEPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SSVEPWidget(QWidget *parent = nullptr);
    ~SSVEPWidget();
    void send(QByteArray);
private slots:
    void recevice();
signals:
    //ssvep进程
private:
    struct HandleData {
         DWORD pid;
         HWND hwnd;
     };
    QProcess *ssvep_process;
    void initProcess();
    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
    HWND findWindowById(DWORD);
};

#endif // SSVEPWIDGET_H
