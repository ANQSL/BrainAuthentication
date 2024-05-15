#include "ssvepwidget.h"
#include "QTimer"
#include "QDebug"
SSVEPWidget::SSVEPWidget(QWidget *parent) : QWidget(parent)
{
    initProcess();
}

SSVEPWidget::~SSVEPWidget()
{
    ssvep_process->kill();
    ssvep_process->waitForFinished();
    delete ssvep_process;
}

void SSVEPWidget::send(QByteArray data)
{
    ssvep_process->write(data);
}
void SSVEPWidget::recevice()
{
    QByteArray data=ssvep_process->readAllStandardOutput();
    QString value=QString::fromUtf8(data);
    if(value.contains("\n"))
    {
        QStringList list=value.split("\r\n");
        for(auto data:list)
        {
            if(!data.isEmpty())
            {
                 qDebug()<<data;
            }
        }
    }
    else
    {
        qDebug()<<value;
    }
}
void SSVEPWidget::initProcess()
{
    ssvep_process=new QProcess;
    ssvep_process->start("D:/project/BrainAuthentication/build-ssvep-Desktop_Qt_5_14_2_MSVC2017_32bit-Debug/test/ssvep_test.exe");
    QTimer::singleShot(1000, this, [=](){
        DWORD pid = ssvep_process->processId();
        HWND hwnd = findWindowById(pid);
        if (hwnd) {
            SetParent(hwnd, (HWND)this->winId());
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_POPUP | WS_CHILD);
            SetWindowPos(hwnd, HWND_TOP, 0, 0, width(),height(), SWP_SHOWWINDOW);
        } else {
           qDebug() << "Failed to find window for PID:" << pid;
        }
    });
    connect(ssvep_process,&QProcess::readyReadStandardOutput,this,&SSVEPWidget::recevice);

}

BOOL SSVEPWidget::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    HandleData& data = *(HandleData*)lParam;
    DWORD windowPid;
    GetWindowThreadProcessId(hwnd, &windowPid);
    if (windowPid == data.pid) {
        data.hwnd = hwnd;
        return FALSE; // 停止枚举
    }
    return TRUE; // 继续枚举
}

HWND SSVEPWidget::findWindowById(DWORD pid)
{
    HandleData data;
    data.pid = pid;
    data.hwnd = NULL;
    EnumWindows(EnumWindowsProc, (LPARAM)&data);
    return data.hwnd;
}
