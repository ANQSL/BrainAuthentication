#ifndef SSVEPCONFIG_H
#define SSVEPCONFIG_H
#include "QList"
#include "QVariant"
class SSVEPConfig
{
public:
    SSVEPConfig();
    QList<QVariant> filckerFrep;//刺激频率
    QList<QVariant> filckerPhi;//刺激相位
    quint16 isi;//两次任务间隔时间
    quint16 display_time;//刺激时长
};

#endif // SSVEPCONFIG_H
