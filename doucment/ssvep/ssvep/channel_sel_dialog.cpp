#include "channel_sel_dialog.h"
#include "ui_channel_sel_dialog.h"
#include <QDebug>
#include <QMessageBox>

extern int chosenChannelNum;
extern int* chosenChannel;



channel_sel_dialog::channel_sel_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::channel_sel_dialog)
{
    ui->setupUi(this);
    for(int i = 0;i<16;i++)
    {
        channelFlag[i] = 0;
    }
}

channel_sel_dialog::~channel_sel_dialog()
{
    delete ui;
    ui = NULL;
}

void channel_sel_dialog::on_pushButton_clicked()
{
    //按确定，检查选择的通道数，chosenChannelNum自加----->chosenChannelNum
    chosenChannelNum = 0;
    if(ui->checkBox_1->checkState())//通道选择打对勾
    {
        chosenChannelNum++;
        channelFlag[0] = 1;
    }
    if(ui->checkBox_2->checkState())
    {
        chosenChannelNum++;
        channelFlag[1] = 1;
    }
    if(ui->checkBox_3->checkState())
    {
        chosenChannelNum++;
        channelFlag[2] = 1;
    }
    if(ui->checkBox_4->checkState())
    {
        chosenChannelNum++;
        channelFlag[3] = 1;
    }
    if(ui->checkBox_5->checkState())
    {
        chosenChannelNum++;
        channelFlag[4] = 1;
    }
    if(ui->checkBox_6->checkState())
    {
        chosenChannelNum++;
        channelFlag[5] = 1;
    }
    if(ui->checkBox_7->checkState())
    {
        chosenChannelNum++;
        channelFlag[6] = 1;
    }
    if(ui->checkBox_8->checkState())
    {
        chosenChannelNum++;
        channelFlag[7] = 1;
    }
    if(ui->checkBox_9->checkState())
    {
        chosenChannelNum++;
        channelFlag[8] = 1;
    }
    if(ui->checkBox_10->checkState())
    {
        chosenChannelNum++;
        channelFlag[9] = 1;
    }
    if(ui->checkBox_11->checkState())
    {
        chosenChannelNum++;
        channelFlag[10] = 1;
    }
    if(ui->checkBox_12->checkState())
    {
        chosenChannelNum++;
        channelFlag[11] = 1;
    }
    if(ui->checkBox_13->checkState())
    {
        chosenChannelNum++;
        channelFlag[12] = 1;
    }
    if(ui->checkBox_14->checkState())
    {
        chosenChannelNum++;
        channelFlag[13] = 1;
    }
    if(ui->checkBox_15->checkState())
    {
        chosenChannelNum++;
        channelFlag[14] = 1;
    }
    if(ui->checkBox_16->checkState())
    {
        chosenChannelNum++;
        channelFlag[15] = 1;
    }
    if(chosenChannel != NULL)//*
    {
        delete [] chosenChannel;
        chosenChannel = NULL;
    }
    chosenChannel = new int[chosenChannelNum];
    qDebug()<<"the chosenChannelNum is : "<<chosenChannelNum;
    int j = 0;
    for(int i = 0;i<16;i++)
    {
        if(1 == channelFlag[i])
        {
            chosenChannel[j] = i;
            j++;
        }
    }
    for(int i = 0;i<chosenChannelNum;i++)
        qDebug()<<"the selected channels are: "<<(chosenChannel[i]+1);
    this->close();






}
