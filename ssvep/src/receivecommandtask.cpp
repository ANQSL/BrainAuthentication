#include "receivecommandtask.h"
#include "windows.h"
#include "iostream"
ReceiveCommandTask::ReceiveCommandTask(QObject *parent) : QThread(parent)
{

}

void ReceiveCommandTask::start()
{
    status=true;
    QThread::start();
}

void ReceiveCommandTask::stop()
{
    status=false;
    QThread::msleep(50);
    terminate();
}
void ReceiveCommandTask::run()
{
    char chBuf[4096];
    DWORD dwRead;
    HANDLE hStdinDup;

    const HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        return;

    DuplicateHandle(GetCurrentProcess(), hStdin,
                    GetCurrentProcess(), &hStdinDup,
                    0, false, DUPLICATE_SAME_ACCESS);

    CloseHandle(hStdin);
    while (status) {
        bool ok = ReadFile(hStdinDup, chBuf, sizeof(chBuf), &dwRead, NULL);
        // emit sig_log(QLatin1String("ok is:")+QString::number(ok));
        if (ok && dwRead != 0)
        {
             emit newCommand(chBuf[0]);
        }
        QThread::usleep(10);
    }
}
