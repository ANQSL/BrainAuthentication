#include "datacommunicate.h"

DataCommunicate::DataCommunicate(QObject *parent) : QObject(parent)
{
    buffer=(double*)malloc(BufferLEN);
    current_point=buffer;
    buffer_data_size=0;

    initCommunicate();
    buildConnection();
}

DataCommunicate::~DataCommunicate()
{
    free(buffer);
    delete communicate;
}

void DataCommunicate::setSrate(quint16 srate)
{
    this->srate=srate;
    clear();
}

void DataCommunicate::start()
{
    this->send_status=true;
}

void DataCommunicate::stop()
{
    this->send_status=false;
}

void DataCommunicate::append(QList<double> data)
{
//    qDebug()<<send_status;
    if(send_status)
    {
        int data_byte_size=sizeof (double)*data.size();
        memcpy(current_point,data.toVector().data(),data_byte_size);
        current_point+=data.size();
        buffer_data_size++;
        if(srate==buffer_data_size)
        {
            communicate->send(buffer,buffer_data_size*data.size());
            clear();
            this->send_time++;
            qDebug()<<"发送次数:"<<send_time;
        }
//        if((srate*0.1)==buffer_data_size)
//        {
//            char point[8]={char(0xFF),char(0xFF),char(0xFF),char(0xFF)
//                          ,char(0xFF),char(0xFF),char(0xFF),char(0xFF)};
//            memcpy(current_point,point,8);
//            communicate->send(buffer,buffer_data_size*data.size()+1);
//            clear();
//            this->send_time++;
//            qDebug()<<"发送次数:"<<send_time;
//        }
    }
    else
    {
        clear();
    }

}

void DataCommunicate::clear()
{
    current_point=buffer;
    buffer_data_size=0;
}

void DataCommunicate::buildConnection()
{
    this->communicate->start();
}

void DataCommunicate::disconnection()
{
    qDebug()<<"连接断开";
    this->communicate->stop();
}

void DataCommunicate::initCommunicate()
{
    communicate=new TcpCommunicate;
    connect(communicate,&TcpCommunicate::result,this,[=](QByteArray value)
    {
        send_status=!send_status;
        send_time=0;
        emit result(value);
    });
    connect(communicate,&TcpCommunicate::readMark,this,&DataCommunicate::readMark);
}
