#include "log.h"
#include "QDateTime"
#include "QDebug"
#include "QFileInfo"
#include "QDir"
Log::Log(QObject *parent) : QObject(parent)
{
    readStartTime();
}
void Log::save(QString msg)
{
    QStringList values;
    QStringList fields=msg.split(",");
    for(int i=0;i<fields.size();i++)
    {
        values.append(fields[i].split("=")[1]);
    }
    save(values[0],values[1]);
}
void Log::save(QString type, QString data)
{
    data=QDateTime::currentDateTime().toString("hh:mm:ss")+":"+data+"\n";
    QString path="log/"+QDateTime::currentDateTime().toString("yyyy-MM-dd")+"/"+QString::number(start_time);
    QFileInfo info(path);
    if(!info.exists())
    {
        QDir dir;
        dir.mkpath(path);
    }
    path=path+"/"+type+".log";
    QFile file(path);
    bool isok=file.open(QIODevice::Append);
    if(isok)
    {
        file.write(data.toUtf8());
    }
    file.close();
}

void Log::readStartTime()
{
     QString path="log/"+QDateTime::currentDateTime().toString("yyyy-MM-dd");
     QFileInfo info(path);
     if(!info.exists())
     {
         QDir dir;
         dir.mkpath(path);
     }
     QDir dir(path);
     start_time=dir.entryList(QDir::Dirs).size();
     start_time++;
}
