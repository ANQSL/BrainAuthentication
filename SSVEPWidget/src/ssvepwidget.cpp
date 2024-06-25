#include "ssvepwidget.h"
#include "QTimer"
#include "QDebug"
#include "QKeyEvent"
SSVEPWidget::SSVEPWidget(QObject *parent) : QObject(parent)
{
    initProcess();
}

SSVEPWidget::~SSVEPWidget()
{
    if(ssvep_process->state()!=QProcess::NotRunning)
    {
        ssvep_process->kill();
        ssvep_process->waitForFinished();
    }
    qDebug()<<"关闭窗口";
    delete ssvep_process;
}

void SSVEPWidget::start()
{
    ssvep_process->start("D:/project/BrainAuthentication/build-ssvep-Desktop_Qt_5_14_2_MSVC2017_32bit-Debug/test/ssvep_test.exe");
    connect(ssvep_process,&QProcess::readyReadStandardOutput,this,&SSVEPWidget::recevice);
}

void SSVEPWidget::stop()
{
    ssvep_process->kill();
}

void SSVEPWidget::display(int model)
{
    QByteArray command;
    command.append(char(model));
    send(command);
}
void SSVEPWidget::show()
{
    QByteArray command;
    command.append(char(0));
    send(command);
}

void SSVEPWidget::hide()
{
    QByteArray command;
    command.append(char(2));
    send(command);
}

void SSVEPWidget::send(QByteArray data)
{
    ssvep_process->write(data);
}

void SSVEPWidget::setParent(QWidget *parent)
{
    if(!is_child)
    {
        DWORD pid = ssvep_process->processId();
        HWND hwnd = findWindowById(pid);
        if (hwnd) {
            SetParent(hwnd, (HWND)parent->winId());
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_POPUP | WS_CHILD);
            SetWindowPos(hwnd, HWND_TOP, 0, 0, 1500,800, SWP_SHOWWINDOW);
            is_child=!is_child;
        } else {
           qDebug() << "Failed to find window for PID:" << pid;
        }
    }
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
    ssvep_process=new QProcess(this);
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
