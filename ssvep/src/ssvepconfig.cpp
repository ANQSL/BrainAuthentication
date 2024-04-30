#include "ssvepconfig.h"
#include "QSettings"
#include "QFileInfo"
SSVEPConfig::SSVEPConfig()
{
    QString config_path="config/ssvep/config.ini";
    QSettings config(config_path,QSettings::IniFormat);
    QVariant var=config.value("filckerFrep");
    if(var.isNull())
    {
        QList<QVariant> filckerFrep={8,8.6,9,9.6,8.4,15.4,8.8,11.8,13.8,15.8};
        QVariant value=QVariant(filckerFrep);
        config.setValue("filckerFrep",value);
        this->filckerFrep=filckerFrep;
    }
    else
    {
        this->filckerFrep=var.toList();
    }
    var=config.value("filckerPhi");
    if(var.isNull())
    {
        QList<QVariant> filckerPhi={0,0.35,0.7,1.05,0.7,0.95,1.4,0.65,0.15,1.65};
        QVariant value=QVariant(filckerPhi);
        config.setValue("filckerPhi",value);
        this->filckerPhi=filckerPhi;
    }
    else
    {
        this->filckerPhi=var.toList();
    }
    var=config.value("isi");
    if(var.isNull())
    {
        QVariant value=500;
        config.setValue("isi",value);
        this->isi=value.toUInt();
    }
    else
    {
        this->isi=var.toUInt();
    }
    var=config.value("display_time");
    if(var.isNull())
    {
        QVariant value=5000;
        config.setValue("display_time",value);
        this->display_time=value.toUInt();
    }
    else
    {
        this->display_time=var.toUInt();
    }
}
