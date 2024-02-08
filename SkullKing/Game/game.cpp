#include "game.h"
#include "ui_game.h"

Game::Game(King *king, QWidget *parent) : QDialog(parent), ui(new Ui::Game)
{
    turn = false;
    this->king = king;
    ui->setupUi(this);
    // this->setCursor(QCursor(QPixmap(":/Resource/Game/cursor.png")));
    ui->KingName->setText(king->username().c_str());
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
    connect(client, &Client::start_round, this, &Game::StartRound);
    client->show();
    client->setModal(true);
    // GameStart("start.txt");
}

void Game::connected_to_server()
{
    client->sendFile(king->filePath().c_str(), "king");
}

void Game::GameStart(string filepath) // for more than 2 players u need to change this function.
{
    opponent_king = new King;
    ifstream file;
    file.open(filepath, ios::in);
    string username;
    Card user_card;
    while (1)
    {
        file >> username;
        if (username != "end.")
        {
            file >> user_card;
            if (username == king->username())
            {
                king->starter_card() = user_card;
            }
            else
            {
                opponent_king->username() = username;
                opponent_king->starter_card() = user_card;
            }
        }
        else
            break;
    }
    file.close();
    ui->OpponentName->setText(opponent_king->username().c_str());
    ui->OpponentCard->show();
    ui->KingCard->show();
    string styleSheet_str("border-image: url(:/Resource/Cards/");
    ui->OpponentCard->setStyleSheet((styleSheet_str + opponent_king->starter_card().filepath() + ");").c_str());
    ui->KingCard->setStyleSheet((styleSheet_str + king->starter_card().filepath() + ");").c_str());
    if (king->starter_card() < opponent_king->starter_card())
        turn = false;
    else
        turn = true;
    client->sendSignal("start_game_ended");
}

void Game::StartRound()
{
    king->load();
    int round = king->hand().size() / 2;
    for (auto &&i : king->hand())
    {
        i.undelete_it();
    }
    sort(king->hand().begin(), king->hand().end());
    ui->KingCard->setStyleSheet("border-image:none;");
    ui->OpponentCard->setStyleSheet("border-image:none;");
    string styleSheet_str("border-image: url(:/Resource/Cards/");
    if (round == 1)
    {
        ui->Card1->show();
        ui->Card2->show();
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->Card1->setStyleSheet((king->hand().at(0).filepath() + ");").c_str());
        ui->Card2->setStyleSheet((king->hand().at(1).filepath() + ");").c_str());
    }
    // else if (round == 2)
    // {
    //     buttons.insert(make_pair(ui->pushButtonCard1, &king->hand().at(0)));
    //     ui->pushButtonCard1->setIcon(QIcon(king->hand().at(0).pixmap()));
    //     ui->pushButtonCard1->setIconSize(king->hand().at(0).pixmap().rect().size());
    //     ui->pushButtonCard1->show();

    //     buttons.insert(make_pair(ui->pushButtonCard2, &king->hand().at(1)));
    //     ui->pushButtonCard2->setIcon(QIcon(king->hand().at(1).pixmap()));
    //     ui->pushButtonCard2->setIconSize(king->hand().at(1).pixmap().rect().size());
    //     ui->pushButtonCard2->show();

    //     buttons.insert(make_pair(ui->pushButtonCard3, &king->hand().at(2)));
    //     ui->pushButtonCard3->setIcon(QIcon(king->hand().at(2).pixmap()));
    //     ui->pushButtonCard3->setIconSize(king->hand().at(2).pixmap().rect().size());
    //     ui->pushButtonCard3->show();

    //     buttons.insert(make_pair(ui->pushButtonCard4, &king->hand().at(3)));
    //     ui->pushButtonCard4->setIcon(QIcon(king->hand().at(3).pixmap()));
    //     ui->pushButtonCard4->setIconSize(king->hand().at(3).pixmap().rect().size());
    //     ui->pushButtonCard4->show();

    //     ui->pushButtonCard5->hide();
    //     ui->pushButtonCard6->hide();
    //     ui->pushButtonCard7->hide();
    //     ui->pushButtonCard8->hide();
    //     ui->pushButtonCard9->hide();
    //     ui->pushButtonCard10->hide();
    //     ui->pushButtonCard11->hide();
    //     ui->pushButtonCard12->hide();
    //     ui->pushButtonCard13->hide();
    //     ui->pushButtonCard14->hide();
    // }
    // else if (round == 3)
    // {
    //     buttons.insert(make_pair(ui->pushButtonCard1, &king->hand().at(0)));
    //     ui->pushButtonCard1->setIcon(QIcon(king->hand().at(0).pixmap()));
    //     ui->pushButtonCard1->setIconSize(king->hand().at(0).pixmap().rect().size());
    //     ui->pushButtonCard1->show();

    //     buttons.insert(make_pair(ui->pushButtonCard2, &king->hand().at(1)));
    //     ui->pushButtonCard2->setIcon(QIcon(king->hand().at(1).pixmap()));
    //     ui->pushButtonCard2->setIconSize(king->hand().at(1).pixmap().rect().size());
    //     ui->pushButtonCard2->show();

    //     buttons.insert(make_pair(ui->pushButtonCard3, &king->hand().at(2)));
    //     ui->pushButtonCard3->setIcon(QIcon(king->hand().at(2).pixmap()));
    //     ui->pushButtonCard3->setIconSize(king->hand().at(2).pixmap().rect().size());
    //     ui->pushButtonCard3->show();

    //     buttons.insert(make_pair(ui->pushButtonCard4, &king->hand().at(3)));
    //     ui->pushButtonCard4->setIcon(QIcon(king->hand().at(3).pixmap()));
    //     ui->pushButtonCard4->setIconSize(king->hand().at(3).pixmap().rect().size());
    //     ui->pushButtonCard4->show();

    //     buttons.insert(make_pair(ui->pushButtonCard5, &king->hand().at(4)));
    //     ui->pushButtonCard5->setIcon(QIcon(king->hand().at(4).pixmap()));
    //     ui->pushButtonCard5->setIconSize(king->hand().at(4).pixmap().rect().size());
    //     ui->pushButtonCard5->show();

    //     buttons.insert(make_pair(ui->pushButtonCard6, &king->hand().at(5)));
    //     ui->pushButtonCard6->setIcon(QIcon(king->hand().at(5).pixmap()));
    //     ui->pushButtonCard6->setIconSize(king->hand().at(5).pixmap().rect().size());
    //     ui->pushButtonCard6->show();

    //     ui->pushButtonCard7->hide();
    //     ui->pushButtonCard8->hide();
    //     ui->pushButtonCard9->hide();
    //     ui->pushButtonCard10->hide();
    //     ui->pushButtonCard11->hide();
    //     ui->pushButtonCard12->hide();
    //     ui->pushButtonCard13->hide();
    //     ui->pushButtonCard14->hide();
    // }
    // else if (round == 4)
    // {
    //     buttons.insert(make_pair(ui->pushButtonCard1, &king->hand().at(0)));
    //     ui->pushButtonCard1->setIcon(QIcon(king->hand().at(0).pixmap()));
    //     ui->pushButtonCard1->setIconSize(king->hand().at(0).pixmap().rect().size());
    //     ui->pushButtonCard1->show();

    //     buttons.insert(make_pair(ui->pushButtonCard2, &king->hand().at(1)));
    //     ui->pushButtonCard2->setIcon(QIcon(king->hand().at(1).pixmap()));
    //     ui->pushButtonCard2->setIconSize(king->hand().at(1).pixmap().rect().size());
    //     ui->pushButtonCard2->show();

    //     buttons.insert(make_pair(ui->pushButtonCard3, &king->hand().at(2)));
    //     ui->pushButtonCard3->setIcon(QIcon(king->hand().at(2).pixmap()));
    //     ui->pushButtonCard3->setIconSize(king->hand().at(2).pixmap().rect().size());
    //     ui->pushButtonCard3->show();

    //     buttons.insert(make_pair(ui->pushButtonCard4, &king->hand().at(3)));
    //     ui->pushButtonCard4->setIcon(QIcon(king->hand().at(3).pixmap()));
    //     ui->pushButtonCard4->setIconSize(king->hand().at(3).pixmap().rect().size());
    //     ui->pushButtonCard4->show();

    //     buttons.insert(make_pair(ui->pushButtonCard5, &king->hand().at(4)));
    //     ui->pushButtonCard5->setIcon(QIcon(king->hand().at(4).pixmap()));
    //     ui->pushButtonCard5->setIconSize(king->hand().at(4).pixmap().rect().size());
    //     ui->pushButtonCard5->show();

    //     buttons.insert(make_pair(ui->pushButtonCard6, &king->hand().at(5)));
    //     ui->pushButtonCard6->setIcon(QIcon(king->hand().at(5).pixmap()));
    //     ui->pushButtonCard6->setIconSize(king->hand().at(5).pixmap().rect().size());
    //     ui->pushButtonCard6->show();

    //     buttons.insert(make_pair(ui->pushButtonCard7, &king->hand().at(6)));
    //     ui->pushButtonCard7->setIcon(QIcon(king->hand().at(6).pixmap()));
    //     ui->pushButtonCard7->setIconSize(king->hand().at(6).pixmap().rect().size());
    //     ui->pushButtonCard7->show();

    //     buttons.insert(make_pair(ui->pushButtonCard8, &king->hand().at(7)));
    //     ui->pushButtonCard8->setIcon(QIcon(king->hand().at(7).pixmap()));
    //     ui->pushButtonCard8->setIconSize(king->hand().at(7).pixmap().rect().size());
    //     ui->pushButtonCard8->show();

    //     ui->pushButtonCard9->hide();
    //     ui->pushButtonCard10->hide();
    //     ui->pushButtonCard11->hide();
    //     ui->pushButtonCard12->hide();
    //     ui->pushButtonCard13->hide();
    //     ui->pushButtonCard14->hide();
    // }
    // else if (round == 5)
    // {
    //     buttons.insert(make_pair(ui->pushButtonCard1, &king->hand().at(0)));
    //     ui->pushButtonCard1->setIcon(QIcon(king->hand().at(0).pixmap()));
    //     ui->pushButtonCard1->setIconSize(king->hand().at(0).pixmap().rect().size());
    //     ui->pushButtonCard1->show();

    //     buttons.insert(make_pair(ui->pushButtonCard2, &king->hand().at(1)));
    //     ui->pushButtonCard2->setIcon(QIcon(king->hand().at(1).pixmap()));
    //     ui->pushButtonCard2->setIconSize(king->hand().at(1).pixmap().rect().size());
    //     ui->pushButtonCard2->show();

    //     buttons.insert(make_pair(ui->pushButtonCard3, &king->hand().at(2)));
    //     ui->pushButtonCard3->setIcon(QIcon(king->hand().at(2).pixmap()));
    //     ui->pushButtonCard3->setIconSize(king->hand().at(2).pixmap().rect().size());
    //     ui->pushButtonCard3->show();

    //     buttons.insert(make_pair(ui->pushButtonCard4, &king->hand().at(3)));
    //     ui->pushButtonCard4->setIcon(QIcon(king->hand().at(3).pixmap()));
    //     ui->pushButtonCard4->setIconSize(king->hand().at(3).pixmap().rect().size());
    //     ui->pushButtonCard4->show();

    //     buttons.insert(make_pair(ui->pushButtonCard5, &king->hand().at(4)));
    //     ui->pushButtonCard5->setIcon(QIcon(king->hand().at(4).pixmap()));
    //     ui->pushButtonCard5->setIconSize(king->hand().at(4).pixmap().rect().size());
    //     ui->pushButtonCard5->show();

    //     buttons.insert(make_pair(ui->pushButtonCard6, &king->hand().at(5)));
    //     ui->pushButtonCard6->setIcon(QIcon(king->hand().at(5).pixmap()));
    //     ui->pushButtonCard6->setIconSize(king->hand().at(5).pixmap().rect().size());
    //     ui->pushButtonCard6->show();

    //     buttons.insert(make_pair(ui->pushButtonCard7, &king->hand().at(6)));
    //     ui->pushButtonCard7->setIcon(QIcon(king->hand().at(6).pixmap()));
    //     ui->pushButtonCard7->setIconSize(king->hand().at(6).pixmap().rect().size());
    //     ui->pushButtonCard7->show();

    //     buttons.insert(make_pair(ui->pushButtonCard8, &king->hand().at(7)));
    //     ui->pushButtonCard8->setIcon(QIcon(king->hand().at(7).pixmap()));
    //     ui->pushButtonCard8->setIconSize(king->hand().at(7).pixmap().rect().size());
    //     ui->pushButtonCard8->show();

    //     buttons.insert(make_pair(ui->pushButtonCard9, &king->hand().at(8)));
    //     ui->pushButtonCard9->setIcon(QIcon(king->hand().at(8).pixmap()));
    //     ui->pushButtonCard9->setIconSize(king->hand().at(8).pixmap().rect().size());
    //     ui->pushButtonCard9->show();

    //     buttons.insert(make_pair(ui->pushButtonCard10, &king->hand().at(9)));
    //     ui->pushButtonCard10->setIcon(QIcon(king->hand().at(9).pixmap()));
    //     ui->pushButtonCard10->setIconSize(king->hand().at(9).pixmap().rect().size());
    //     ui->pushButtonCard10->show();

    //     ui->pushButtonCard11->hide();
    //     ui->pushButtonCard12->hide();
    //     ui->pushButtonCard13->hide();
    //     ui->pushButtonCard14->hide();
    // }
    // else if (round == 6)
    // {
    //     buttons.insert(make_pair(ui->pushButtonCard1, &king->hand().at(0)));
    //     ui->pushButtonCard1->setIcon(QIcon(king->hand().at(0).pixmap()));
    //     ui->pushButtonCard1->setIconSize(king->hand().at(0).pixmap().rect().size());
    //     ui->pushButtonCard1->show();

    //     buttons.insert(make_pair(ui->pushButtonCard2, &king->hand().at(1)));
    //     ui->pushButtonCard2->setIcon(QIcon(king->hand().at(1).pixmap()));
    //     ui->pushButtonCard2->setIconSize(king->hand().at(1).pixmap().rect().size());
    //     ui->pushButtonCard2->show();

    //     buttons.insert(make_pair(ui->pushButtonCard3, &king->hand().at(2)));
    //     ui->pushButtonCard3->setIcon(QIcon(king->hand().at(2).pixmap()));
    //     ui->pushButtonCard3->setIconSize(king->hand().at(2).pixmap().rect().size());
    //     ui->pushButtonCard3->show();

    //     buttons.insert(make_pair(ui->pushButtonCard4, &king->hand().at(3)));
    //     ui->pushButtonCard4->setIcon(QIcon(king->hand().at(3).pixmap()));
    //     ui->pushButtonCard4->setIconSize(king->hand().at(3).pixmap().rect().size());
    //     ui->pushButtonCard4->show();

    //     buttons.insert(make_pair(ui->pushButtonCard5, &king->hand().at(4)));
    //     ui->pushButtonCard5->setIcon(QIcon(king->hand().at(4).pixmap()));
    //     ui->pushButtonCard5->setIconSize(king->hand().at(4).pixmap().rect().size());
    //     ui->pushButtonCard5->show();

    //     buttons.insert(make_pair(ui->pushButtonCard6, &king->hand().at(5)));
    //     ui->pushButtonCard6->setIcon(QIcon(king->hand().at(5).pixmap()));
    //     ui->pushButtonCard6->setIconSize(king->hand().at(5).pixmap().rect().size());
    //     ui->pushButtonCard6->show();

    //     buttons.insert(make_pair(ui->pushButtonCard7, &king->hand().at(6)));
    //     ui->pushButtonCard7->setIcon(QIcon(king->hand().at(6).pixmap()));
    //     ui->pushButtonCard7->setIconSize(king->hand().at(6).pixmap().rect().size());
    //     ui->pushButtonCard7->show();

    //     buttons.insert(make_pair(ui->pushButtonCard8, &king->hand().at(7)));
    //     ui->pushButtonCard8->setIcon(QIcon(king->hand().at(7).pixmap()));
    //     ui->pushButtonCard8->setIconSize(king->hand().at(7).pixmap().rect().size());
    //     ui->pushButtonCard8->show();

    //     buttons.insert(make_pair(ui->pushButtonCard9, &king->hand().at(8)));
    //     ui->pushButtonCard9->setIcon(QIcon(king->hand().at(8).pixmap()));
    //     ui->pushButtonCard9->setIconSize(king->hand().at(8).pixmap().rect().size());
    //     ui->pushButtonCard9->show();

    //     buttons.insert(make_pair(ui->pushButtonCard10, &king->hand().at(9)));
    //     ui->pushButtonCard10->setIcon(QIcon(king->hand().at(9).pixmap()));
    //     ui->pushButtonCard10->setIconSize(king->hand().at(9).pixmap().rect().size());
    //     ui->pushButtonCard10->show();

    //     buttons.insert(make_pair(ui->pushButtonCard11, &king->hand().at(10)));
    //     ui->pushButtonCard11->setIcon(QIcon(king->hand().at(10).pixmap()));
    //     ui->pushButtonCard11->setIconSize(king->hand().at(10).pixmap().rect().size());
    //     ui->pushButtonCard11->show();

    //     buttons.insert(make_pair(ui->pushButtonCard12, &king->hand().at(11)));
    //     ui->pushButtonCard12->setIcon(QIcon(king->hand().at(11).pixmap()));
    //     ui->pushButtonCard12->setIconSize(king->hand().at(11).pixmap().rect().size());
    //     ui->pushButtonCard12->show();

    //     ui->pushButtonCard13->hide();
    //     ui->pushButtonCard14->hide();
    // }
    // else if (round == 7)
    // {
    //     buttons.insert(make_pair(ui->pushButtonCard1, &king->hand().at(0)));
    //     ui->pushButtonCard1->setIcon(QIcon(king->hand().at(0).pixmap()));
    //     ui->pushButtonCard1->setIconSize(king->hand().at(0).pixmap().rect().size());
    //     ui->pushButtonCard1->show();

    //     buttons.insert(make_pair(ui->pushButtonCard2, &king->hand().at(1)));
    //     ui->pushButtonCard2->setIcon(QIcon(king->hand().at(1).pixmap()));
    //     ui->pushButtonCard2->setIconSize(king->hand().at(1).pixmap().rect().size());
    //     ui->pushButtonCard2->show();

    //     buttons.insert(make_pair(ui->pushButtonCard3, &king->hand().at(2)));
    //     ui->pushButtonCard3->setIcon(QIcon(king->hand().at(2).pixmap()));
    //     ui->pushButtonCard3->setIconSize(king->hand().at(2).pixmap().rect().size());
    //     ui->pushButtonCard3->show();

    //     buttons.insert(make_pair(ui->pushButtonCard4, &king->hand().at(3)));
    //     ui->pushButtonCard4->setIcon(QIcon(king->hand().at(3).pixmap()));
    //     ui->pushButtonCard4->setIconSize(king->hand().at(3).pixmap().rect().size());
    //     ui->pushButtonCard4->show();

    //     buttons.insert(make_pair(ui->pushButtonCard5, &king->hand().at(4)));
    //     ui->pushButtonCard5->setIcon(QIcon(king->hand().at(4).pixmap()));
    //     ui->pushButtonCard5->setIconSize(king->hand().at(4).pixmap().rect().size());
    //     ui->pushButtonCard5->show();

    //     buttons.insert(make_pair(ui->pushButtonCard6, &king->hand().at(5)));
    //     ui->pushButtonCard6->setIcon(QIcon(king->hand().at(5).pixmap()));
    //     ui->pushButtonCard6->setIconSize(king->hand().at(5).pixmap().rect().size());
    //     ui->pushButtonCard6->show();

    //     buttons.insert(make_pair(ui->pushButtonCard7, &king->hand().at(6)));
    //     ui->pushButtonCard7->setIcon(QIcon(king->hand().at(6).pixmap()));
    //     ui->pushButtonCard7->setIconSize(king->hand().at(6).pixmap().rect().size());
    //     ui->pushButtonCard7->show();

    //     buttons.insert(make_pair(ui->pushButtonCard8, &king->hand().at(7)));
    //     ui->pushButtonCard8->setIcon(QIcon(king->hand().at(7).pixmap()));
    //     ui->pushButtonCard8->setIconSize(king->hand().at(7).pixmap().rect().size());
    //     ui->pushButtonCard8->show();

    //     buttons.insert(make_pair(ui->pushButtonCard9, &king->hand().at(8)));
    //     ui->pushButtonCard9->setIcon(QIcon(king->hand().at(8).pixmap()));
    //     ui->pushButtonCard9->setIconSize(king->hand().at(8).pixmap().rect().size());
    //     ui->pushButtonCard9->show();

    //     buttons.insert(make_pair(ui->pushButtonCard10, &king->hand().at(9)));
    //     ui->pushButtonCard10->setIcon(QIcon(king->hand().at(9).pixmap()));
    //     ui->pushButtonCard10->setIconSize(king->hand().at(9).pixmap().rect().size());
    //     ui->pushButtonCard10->show();

    //     buttons.insert(make_pair(ui->pushButtonCard11, &king->hand().at(10)));
    //     ui->pushButtonCard11->setIcon(QIcon(king->hand().at(10).pixmap()));
    //     ui->pushButtonCard11->setIconSize(king->hand().at(10).pixmap().rect().size());
    //     ui->pushButtonCard11->show();

    //     buttons.insert(make_pair(ui->pushButtonCard12, &king->hand().at(11)));
    //     ui->pushButtonCard12->setIcon(QIcon(king->hand().at(11).pixmap()));
    //     ui->pushButtonCard12->setIconSize(king->hand().at(11).pixmap().rect().size());
    //     ui->pushButtonCard12->show();

    //     buttons.insert(make_pair(ui->pushButtonCard13, &king->hand().at(12)));
    //     ui->pushButtonCard13->setIcon(QIcon(king->hand().at(12).pixmap()));
    //     ui->pushButtonCard13->setIconSize(king->hand().at(12).pixmap().rect().size());
    //     ui->pushButtonCard13->show();

    //     buttons.insert(make_pair(ui->pushButtonCard14, &king->hand().at(13)));
    //     ui->pushButtonCard14->setIcon(QIcon(king->hand().at(13).pixmap()));
    //     ui->pushButtonCard14->setIconSize(king->hand().at(13).pixmap().rect().size());
    //     ui->pushButtonCard14->show();
    // }

    // will = new WillWin(round, this);
    // will->setModal(true);
    // will->exec();
    // if (will->result() == WillWin::Accepted)
    // {
    //     will_win = will->getWill_win();
    //     delete will;
    // }
    // else if (will->result() == WillWin::Rejected)
    // {
    //     will_win = 0;
    // }
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
