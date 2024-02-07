#ifndef GAME_H
#define GAME_H

#include "MyClasses/king.h"
#include "MyClasses/card.h"
#include "Game/client.h"
#include <QDialog>
#include <unordered_map>

namespace Ui
{
    class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(King *king, QWidget *parent = nullptr);
    ~Game();

private slots:
    void card_clicked();
    void GameStart();

private:
    Ui::Game *ui;
    King *king;
    Client *client;
    unordered_map<QPushButton *, Card *> king_cards;
    unordered_map<QPushButton *, Card *>::iterator card;
};

#endif // GAME_H
