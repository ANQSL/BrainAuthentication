#include "start_game.h"
#include "ui_start_game.h"

#include "QDebug"

start_game::start_game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start_game)
{
    ui->setupUi(this);
    ui->start_btn->setStyleSheet("QPushButton{background: #FFFFFF;font: 16pt Alibaba PuHuiTi 2.0; color: rgb(255, 255, 255);background: linear-gradient(180deg, #487FD4 0%, #4FD7EE 100%);border-radius: 8px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #487FD4, stop:1 #4FD7EE);}");

}
void start_game::addGame(QList<GameData> data)
{
    for(QList<GameData>::iterator begin=data.begin();begin!=data.end();begin++)
    {
        QListWidgetItem *item=new QListWidgetItem((*begin).icon,(*begin).name);
        ui->game_list->addItem(item);
    }
    ui->game_icon->setPixmap(data[0].icon.pixmap(ui->game_icon->size()));
}
start_game::~start_game()
{
    delete ui;
}

void start_game::on_game_list_itemPressed(QListWidgetItem *item)
{
    QIcon icon=item->icon();
    ui->game_icon->setPixmap(icon.pixmap(ui->game_icon->size()));
}


void start_game::on_start_btn_clicked()
{
    emit start(0);
}
