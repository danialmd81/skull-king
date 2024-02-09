#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include "MyClasses/king.h"
#include "MyClasses/card.h"
#include "Game/client.h"
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
    void on_Stop_clicked();
    void connected_to_server();
    void StartGame(std::string filepath);
    void StartRound();
    void play_card();

private:
    Ui::Game *ui;
    King *king, *opponent_king;
    bool turn;
    int round;
    Client *client;
    unordered_map<QPushButton *, Card *> king_cards;
    unordered_map<QPushButton *, Card *>::iterator card;
    Card *op_card, *k_card;

    void set_card(QPushButton *, Card);
    void set_card(QLabel *, Card);
    void unset_card(QPushButton *);
    void unset_card(QLabel *);
};

#endif // GAME_H
