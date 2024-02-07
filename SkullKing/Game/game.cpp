#include "game.h"
#include "ui_game.h"

Game::Game(King *king, QWidget *parent) : QDialog(parent), ui(new Ui::Game)
{
    this->king = king;
    ui->setupUi(this);
    // this->setCursor(QCursor(QPixmap(":/Resource/Game/cursor.png")));
    ui->KingName->setText(king->name().c_str());
    connect(ui->Card1, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card2, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card3, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card4, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card5, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card6, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card7, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card8, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card9, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card10, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card11, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card12, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card13, &QPushButton::clicked, this, &Game::card_clicked);
    connect(ui->Card14, &QPushButton::clicked, this, &Game::card_clicked);
    ui->Card1->hide();
    ui->Card2->hide();
    ui->Card3->hide();
    ui->Card4->hide();
    ui->Card5->hide();
    ui->Card6->hide();
    ui->Card7->hide();
    ui->Card8->hide();
    ui->Card9->hide();
    ui->Card10->hide();
    ui->Card11->hide();
    ui->Card12->hide();
    ui->Card13->hide();
    ui->Card14->hide();
    ui->BackCard_1->hide();
    ui->BackCard_2->hide();
    ui->BackCard_3->hide();
    ui->BackCard_4->hide();
    ui->BackCard_5->hide();
    ui->BackCard_6->hide();
    ui->BackCard_7->hide();
    ui->BackCard_8->hide();
    ui->BackCard_9->hide();
    ui->BackCard_10->hide();
    ui->BackCard_11->hide();
    ui->BackCard_12->hide();
    ui->BackCard_13->hide();
    ui->BackCard_14->hide();
    ui->KingCard->hide();
    ui->OpponentCard->hide();
    this->showFullScreen();
    client = new Client(this);
    connect(client, &Client::connected_to_server, this, &Game::connected_to_server);
    connect(client, &Client::start_game, this, &Game::GameStart);
    connect(client, &Client::oppnent_king, this, &Game::oppnent_king);
    client->exec();
}

void Game::connected_to_server()
{
    client->sendFile(king->filePath().c_str(), "king");
}

void Game::oppnent_king(string filepath) // for more than 2 players u need to change this function.
{
    opponent_king = new King;
    opponent_king->load(filepath); // should check if filepath is correct or not.
    ui->OpponentName->setText(opponent_king->name().c_str());
}

void Game::GameStart()
{
}

void Game::card_clicked()
{
    // QPushButton *selected_card = reinterpret_cast<QPushButton *>(sender());
    // card = king_cards.find(selected_card);

    // if (king->turn())
    // {
    //     if (ui->CardLabel1->pixmap().isNull() && ui->CardLabel2->pixmap().isNull()) // for first player
    //     {
    //         ui->CardLabel1->setPixmap(button->second->pixmap());
    //         selected_card->hide();
    //         button->second->delete_it();
    //         button->second->save();
    //         king->turn() = false;
    //         client->sendFile("card.txt", "play_card");
    //     }

    //     else if (ui->CardLabel1->pixmap().isNull() && !ui->CardLabel2->pixmap().isNull()) // for second player
    //     {
    //         if (button->second->compare(ground) == -1)
    //         {
    //             ui->CardLabel1->setPixmap(button->second->pixmap());
    //             button->first->hide();
    //             button->second->delete_it();
    //             button->second->save();
    //             king->turn() = false;
    //             QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
    //             client->sendFile("card.txt", "play_card");
    //         }
    //         else if (button->second->compare(ground) == 0)
    //         {
    //             auto it = std::find(king->hand().begin(), king->hand().end(), ground);
    //             if (it != king->hand().end())
    //             {
    //                 if (!it->is_deleted())
    //                 {
    //                     QMessageBox::critical(this, "Wrong Choose", "Choose Wisly");
    //                     return;
    //                 }
    //                 else
    //                 {
    //                     ui->CardLabel1->setPixmap(button->second->pixmap());
    //                     button->first->hide();
    //                     button->second->delete_it();
    //                     button->second->save();
    //                     king->turn() = false;
    //                     QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
    //                     client->sendFile("card.txt", "play_card");
    //                 }
    //             }
    //             else
    //             {
    //                 ui->CardLabel1->setPixmap(button->second->pixmap());
    //                 button->first->hide();
    //                 button->second->delete_it();
    //                 button->second->save();
    //                 king->turn() = false;
    //                 QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
    //                 client->sendFile("card.txt", "play_card");
    //             }
    //         }

    //         else if (button->second->compare(ground) == 1)
    //         {
    //             ui->CardLabel1->setPixmap(button->second->pixmap());
    //             button->first->hide();
    //             button->second->delete_it();
    //             button->second->save();
    //             winning_card++;
    //             king->turn() = false;
    //             QMessageBox::information(this, "Win a Hand", "You Won this Hand");
    //             client->sendFile("card.txt", "play_card");
    //         }

    //         else if (button->second->compare(ground) == 2)
    //         {
    //             ui->CardLabel1->setPixmap(button->second->pixmap());
    //             button->first->hide();
    //             button->second->delete_it();
    //             button->second->save();
    //             king->turn() = false;
    //             QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
    //             client->sendFile("card.txt", "play_card");
    //         }

    //         else
    //         {
    //             QMessageBox::critical(this, "Wrong Choose", "Choose Wisly");
    //             return;
    //         }

    //         ui->CardLabel1->clear();
    //         ui->CardLabel2->clear();

    //         if (king->hand_is_empty())
    //         {
    //             king_cards.clear();
    //             king->hand().clear();

    //             ofstream file;
    //             file.open("round.txt", ios::out | ios::trunc);
    //             file << round;
    //             file.close();
    //             round++;

    //             // proces score here

    //             QTest::qWait(500);
    //             client->sendFile("round.txt", "round_ended");
    //         }
    //     }
    // }

    // else
    // {
    //     QMessageBox::critical(this, "Turn", "It is not your turn");
    // }
}

Game::~Game()
{
    delete ui;
}

void Game::on_Stop_clicked()
{
}
