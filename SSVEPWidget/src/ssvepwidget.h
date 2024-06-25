#ifndef SSVEPWIDGET_H
#define SSVEPWIDGET_H

#include <QWidget>
#include "QProcess"
#include "Windows.h"
class SSVEPWidget : public QObject
{
    Q_OBJECT
public:
    explicit SSVEPWidget(QObject *parent = nullptr);
    ~SSVEPWidget();
    void start();
    void stop();
    //1:采集模式，2:识别模式
    void display(int);
    void show();
    void hide();
    void send(QByteArray);
    //设置父窗口
    void setParent(QWidget*);
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
    bool is_child=false;
};

#endif // SSVEPWIDGET_H
