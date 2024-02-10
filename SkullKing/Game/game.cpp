#include "game.h"
#include "ui_game.h"

Game::Game(King *king, QWidget *parent) : QDialog(parent), ui(new Ui::Game)
{
    turn = false;
    this->king = new King(*king);
    op_card = nullptr;
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
    connect(client, &Client::start_game, this, &Game::StartGame);
    connect(client, &Client::start_round, this, &Game::StartRound);
    connect(client, &Client::play_card, this, &Game::PlayCard);
    client->show();
    client->setModal(true);
    // GameStart("start.txt");//it's for testing
    // StartRound();//it's for testing
}

void Game::connected_to_server()
{
    client->sendFile(king->filePath().c_str(), "king");
}

void Game::set_card(QPushButton *button, Card card)
{
    button->show();
    string styleSheet_str("border-image: url(:/Resource/Cards/");
    button->setStyleSheet((styleSheet_str + card.filepath() + ");").c_str());
}

void Game::set_card(QLabel *label, Card card)
{
    label->show();
    string styleSheet_str("border-image: url(:/Resource/Cards/");
    label->setStyleSheet((styleSheet_str + card.filepath() + ");").c_str());
}

void Game::unset_card(QPushButton *button)
{
    button->setStyleSheet("border-image:none;");
    button->hide();
}

void Game::unset_card(QLabel *label)
{
    label->setStyleSheet("border-image:none;");
    label->hide();
}

void Game::StartGame(string filepath) // for more than 2 players u need to change this function.
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
    set_card(ui->OpponentCard, opponent_king->starter_card());
    set_card(ui->KingCard, king->starter_card());
    if (king->starter_card() < opponent_king->starter_card())
        turn = false;
    else
        turn = true;
    client->sendSignal("start_game_ended");
}

void Game::StartRound()
{
    king->reset_hand();
    king->load(); // it's for real
    unset_card(ui->KingCard);
    unset_card(ui->OpponentCard);
    int round = king->hand().size() / 2;
    for (auto &&i : king->hand())
    {
        i.undelete_it();
    }
    sort(king->hand().begin(), king->hand().end());
    // turn = true; // it's for testing
    if (round == 1)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        // play_card(); // it's for testing
    }
    else if (round == 2)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        set_card(ui->Card3, king->hand().at(2));
        set_card(ui->Card4, king->hand().at(3));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->BackCard_3->show();
        ui->BackCard_4->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        king_cards.insert(pair(ui->Card3, &king->hand().at(2)));
        king_cards.insert(pair(ui->Card4, &king->hand().at(3)));
    }
    else if (round == 3)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        set_card(ui->Card3, king->hand().at(2));
        set_card(ui->Card4, king->hand().at(3));
        set_card(ui->Card5, king->hand().at(4));
        set_card(ui->Card6, king->hand().at(5));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->BackCard_3->show();
        ui->BackCard_4->show();
        ui->BackCard_5->show();
        ui->BackCard_6->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        king_cards.insert(pair(ui->Card3, &king->hand().at(2)));
        king_cards.insert(pair(ui->Card4, &king->hand().at(3)));
        king_cards.insert(pair(ui->Card5, &king->hand().at(4)));
        king_cards.insert(pair(ui->Card6, &king->hand().at(5)));
    }

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
    QPushButton *selected_card = reinterpret_cast<QPushButton *>(sender());
    auto card = king_cards.find(selected_card);
    // turn = true;//it's for testing
    if (turn)
    {
        if (ui->KingCard->isHidden() && ui->OpponentCard->isHidden()) // for first hand play
        {
            set_card(ui->KingCard, *card->second);
            selected_card->hide();
            card->second->delete_it();
            card->second->save();
            k_card = card->second;
            turn = false;
        }
        else if (ui->KingCard->isHidden() && !ui->OpponentCard->isHidden()) // for second player
        {
            if (card->second->compare(*op_card) == -1)
            {
                set_card(ui->KingCard, *card->second);
                selected_card->hide();
                card->second->delete_it();
                card->second->save();
                turn = false;
                QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
            }
            else if (card->second->compare(*op_card) == 0)
            {
                auto it = std::find(king->hand().begin(), king->hand().end(), *op_card);
                if (it != king->hand().end())
                {
                    if (!it->is_deleted())
                    {
                        QMessageBox::critical(this, "Wrong Choose", "Choose Wisly");
                        return;
                    }
                    else
                    {
                        set_card(ui->KingCard, *card->second);
                        selected_card->hide();
                        card->second->delete_it();
                        card->second->save();
                        turn = false;
                        QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
                    }
                }
                else
                {
                    set_card(ui->KingCard, *card->second);
                    selected_card->hide();
                    card->second->delete_it();
                    card->second->save();
                    turn = false;
                    QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
                }
            }
            else if (card->second->compare(*op_card) == 1)
            {
                set_card(ui->KingCard, *card->second);
                selected_card->hide();
                card->second->delete_it();
                card->second->save();
                turn = false;
                // winning_card++;
                QMessageBox::information(this, "Win a Hand", "You Won this Hand");
            }
            else if (card->second->compare(*op_card) == 2)
            {
                set_card(ui->KingCard, *card->second);
                selected_card->hide();
                card->second->delete_it();
                card->second->save();
                turn = false;
                QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
            }
            else
            {
                QMessageBox::critical(this, "Wrong Choose", "Choose Wisly");
                return;
            }
            unset_card(ui->KingCard);
            unset_card(ui->OpponentCard);
            delete op_card;
            if (king->all_cards_is_deleted())
            {
                king_cards.clear();
                king->reset_hand();
                // proces score here
                client->sendSignal("next_round");
            }
        }
        client->sendFile("card.txt", "play_card");
    }
    else
    {
        QMessageBox::critical(this, "Turn", "It is not your turn");
    }
}

bool Game::is_all_BackCard_hidden()
{
    if (ui->BackCard_1->isHidden() && ui->BackCard_2->isHidden() && ui->BackCard_3->isHidden() && ui->BackCard_4->isHidden() && ui->BackCard_5->isHidden() && ui->BackCard_6->isHidden() && ui->BackCard_7->isHidden() && ui->BackCard_8->isHidden() && ui->BackCard_9->isHidden() && ui->BackCard_10->isHidden() && ui->BackCard_11->isHidden() && ui->BackCard_12->isHidden() && ui->BackCard_13->isHidden() && ui->BackCard_14->isHidden())
        return true;
    return false;
}

void Game::PlayCard()
{
    op_card = new Card;
    op_card->load();
    set_card(ui->OpponentCard, *op_card);
    turn = true;
    if (!ui->KingCard->isHidden() && !ui->OpponentCard->isHidden())
    {
        if (k_card->compare(*op_card) == -1)
        {
            QMessageBox::information(this, "Loose a Hand", "You Loosed this Hand");
        }
        else if (k_card->compare(*op_card) == 0) // should check
        {
            // winning_card++;
            QMessageBox::information(this, "Win a Hand", "You Won this Hand");
        }

        else if (k_card->compare(*op_card) == 1)
        {
            // winning_card++;
            QMessageBox::information(this, "Win a Hand", "You Won this Hand");
        }
        else if (k_card->compare(*op_card) == 2)
        {
            // winning_card++;
            QMessageBox::information(this, "Win a Hand", "You Won this Hand");
        }
        else
        {
            QMessageBox::critical(this, "Wrong Choose", "Choose Wisly");
            return;
        }
        unset_card(ui->KingCard);
        unset_card(ui->OpponentCard);
        delete op_card;
    }
    if (!ui->BackCard_1->isHidden())
    {
        ui->BackCard_1->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_2->isHidden())
    {
        ui->BackCard_2->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_3->isHidden())
    {
        ui->BackCard_3->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_4->isHidden())
    {
        ui->BackCard_4->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_5->isHidden())
    {
        ui->BackCard_5->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_6->isHidden())
    {
        ui->BackCard_6->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_7->isHidden())
    {
        ui->BackCard_7->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_8->isHidden())
    {
        ui->BackCard_8->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_9->isHidden())
    {
        ui->BackCard_9->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_10->isHidden())
    {
        ui->BackCard_10->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_11->isHidden())
    {
        ui->BackCard_11->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_12->isHidden())
    {
        ui->BackCard_12->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_13->isHidden())
    {
        ui->BackCard_13->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
    else if (!ui->BackCard_14->isHidden())
    {
        ui->BackCard_14->hide();
        if (is_all_BackCard_hidden())
        {
            // proces score here
            client->sendSignal("next_round");
        }
        return;
    }
}

Game::~Game()
{
    delete ui;
}

void Game::on_Stop_clicked()
{
}
