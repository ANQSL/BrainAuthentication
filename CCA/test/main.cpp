#include "cca.h"
#include"QCoreApplication"
#include "QFile"
#include "QDir"
#include "QDebug"
#include "iostream"
CCA cca;
double ssvep_data[32][5000]={{0}};
bool read_ssvep_data(QString path,double *data)
{
    QFile file(path);
    bool isok=file.open(QIODevice::ReadOnly);
    if(isok)
    {
        QByteArray file_data =file.readAll();
        for(int i=0;i<32;i++)
        {
            memcpy(data+5000*i,file_data.data()+5000*i*sizeof (8),sizeof (double)*5000);
        }
        return true;
    }
    return false;

}
bool ssvep_classify(QString path)
{
    QDir dir(path);
    QStringList name_filters;
    name_filters<<"*.bin";
    QStringList result=dir.entryList(name_filters,QDir::Files | QDir::Readable,QDir::Name);
    for(auto file_path:result)
    {
        qDebug()<<file_path;
        read_ssvep_data(path+"/"+file_path,ssvep_data[0]);
        qDebug()<<cca.Classify(ssvep_data,32);
    }
    return false;
}
int main(int args,char **argv)
{
   ssvep_classify("D:/project/BrainAuthentication/test");
}
