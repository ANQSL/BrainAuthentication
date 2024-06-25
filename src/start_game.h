#ifndef START_GAME_H
#define START_GAME_H
#include "QListWidgetItem"
#include <QWidget>

namespace Ui {
class start_game;
}

class start_game : public QWidget
{
    Q_OBJECT
public:
    typedef  struct
    {
      QIcon icon;
      QString name;
    }GameData;
    explicit start_game(QWidget *parent = nullptr);
    ~start_game();
    void addGame(QList<GameData>);
    QWidget* getSSVEPWidget();

signals:
    void start(int id);
    void collection();

private slots:
    void on_game_list_itemPressed(QListWidgetItem *item);

    void on_start_btn_clicked();

    void on_collection_clicked();

private:
    Ui::start_game *ui;
    QList<QListWidgetItem *> game;

};

#endif // START_GAME_H
