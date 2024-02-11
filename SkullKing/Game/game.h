#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
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
    void on_Exit_clicked();
    void connected_to_server();
    void StartGame(std::string filepath);
    void StartRound();
    void PlayCard();
    void Pause();

private:
    Ui::Game *ui;
    King *king, *opponent_king;
    bool turn;
    Client *client;
    unordered_map<QPushButton *, Card *> king_cards;
    Card *op_card, *k_card;

    void set_card(QPushButton *, Card);
    void set_card(QLabel *, Card);
    void unset_card(QPushButton *);
    void unset_card(QLabel *);
    bool is_all_king_cards_played();
    void backCard_handling();
};

#endif // GAME_H
