#include "QCoreApplication"
#include "log.h"
int main(int args,char **argv)
{
    Log log;
    for(int i=0;i<10;i++)
    {
       log.save("MsgType=ftp,data=123123");
    }
}
