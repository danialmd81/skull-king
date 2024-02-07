#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "Game/game.h"
#include "MyClasses/king.h"
namespace Ui
{
    class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(King *king, QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_Logout_clicked();
    void on_Exit_clicked();
    void on_StartGame_clicked();
    void on_History_clicked();
    void on_ChangeProfile_clicked();
    void game_slot();

private:
    Ui::Menu *ui;
    Game *game;
    King *king;
};

#endif // MENU_H
