#include "game.h"
#include "ui_game.h"

Game::Game(King *king, QWidget *parent) : QDialog(parent), ui(new Ui::Game)
{
    turn = false;
    this->king = new King(*king);
    op_card = nullptr;
    ui->setupUi(this);
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
    connect(client, &Client::pause, this, Game::Pause);
    connect(client, Client::resume, this, Game::Resume);
    client->show();
    client->setModal(true);
}

Game::~Game()
{
    delete ui;
}

void Game::connected_to_server()
{
    client->sendFile(king->filePath().c_str(), "king");
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
    king_cards.clear();
    king->load();
    unset_card(ui->KingCard);
    unset_card(ui->OpponentCard);
    int round = king->hand().size() / 2;
    sort(king->hand().begin(), king->hand().end());

    if (round == 1)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
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
    else if (round == 4)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        set_card(ui->Card3, king->hand().at(2));
        set_card(ui->Card4, king->hand().at(3));
        set_card(ui->Card5, king->hand().at(4));
        set_card(ui->Card6, king->hand().at(5));
        set_card(ui->Card7, king->hand().at(6));
        set_card(ui->Card8, king->hand().at(7));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->BackCard_3->show();
        ui->BackCard_4->show();
        ui->BackCard_5->show();
        ui->BackCard_6->show();
        ui->BackCard_7->show();
        ui->BackCard_8->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        king_cards.insert(pair(ui->Card3, &king->hand().at(2)));
        king_cards.insert(pair(ui->Card4, &king->hand().at(3)));
        king_cards.insert(pair(ui->Card5, &king->hand().at(4)));
        king_cards.insert(pair(ui->Card6, &king->hand().at(5)));
        king_cards.insert(pair(ui->Card7, &king->hand().at(6)));
        king_cards.insert(pair(ui->Card8, &king->hand().at(7)));
    }
    else if (round == 5)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        set_card(ui->Card3, king->hand().at(2));
        set_card(ui->Card4, king->hand().at(3));
        set_card(ui->Card5, king->hand().at(4));
        set_card(ui->Card6, king->hand().at(5));
        set_card(ui->Card7, king->hand().at(6));
        set_card(ui->Card8, king->hand().at(7));
        set_card(ui->Card9, king->hand().at(8));
        set_card(ui->Card10, king->hand().at(9));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->BackCard_3->show();
        ui->BackCard_4->show();
        ui->BackCard_5->show();
        ui->BackCard_6->show();
        ui->BackCard_7->show();
        ui->BackCard_8->show();
        ui->BackCard_9->show();
        ui->BackCard_10->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        king_cards.insert(pair(ui->Card3, &king->hand().at(2)));
        king_cards.insert(pair(ui->Card4, &king->hand().at(3)));
        king_cards.insert(pair(ui->Card5, &king->hand().at(4)));
        king_cards.insert(pair(ui->Card6, &king->hand().at(5)));
        king_cards.insert(pair(ui->Card7, &king->hand().at(6)));
        king_cards.insert(pair(ui->Card8, &king->hand().at(7)));
        king_cards.insert(pair(ui->Card9, &king->hand().at(8)));
        king_cards.insert(pair(ui->Card10, &king->hand().at(9)));
    }
    else if (round == 6)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        set_card(ui->Card3, king->hand().at(2));
        set_card(ui->Card4, king->hand().at(3));
        set_card(ui->Card5, king->hand().at(4));
        set_card(ui->Card6, king->hand().at(5));
        set_card(ui->Card7, king->hand().at(6));
        set_card(ui->Card8, king->hand().at(7));
        set_card(ui->Card9, king->hand().at(8));
        set_card(ui->Card10, king->hand().at(9));
        set_card(ui->Card11, king->hand().at(10));
        set_card(ui->Card12, king->hand().at(11));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->BackCard_3->show();
        ui->BackCard_4->show();
        ui->BackCard_5->show();
        ui->BackCard_6->show();
        ui->BackCard_7->show();
        ui->BackCard_8->show();
        ui->BackCard_9->show();
        ui->BackCard_10->show();
        ui->BackCard_11->show();
        ui->BackCard_12->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        king_cards.insert(pair(ui->Card3, &king->hand().at(2)));
        king_cards.insert(pair(ui->Card4, &king->hand().at(3)));
        king_cards.insert(pair(ui->Card5, &king->hand().at(4)));
        king_cards.insert(pair(ui->Card6, &king->hand().at(5)));
        king_cards.insert(pair(ui->Card7, &king->hand().at(6)));
        king_cards.insert(pair(ui->Card8, &king->hand().at(7)));
        king_cards.insert(pair(ui->Card9, &king->hand().at(8)));
        king_cards.insert(pair(ui->Card10, &king->hand().at(9)));
        king_cards.insert(pair(ui->Card11, &king->hand().at(10)));
        king_cards.insert(pair(ui->Card12, &king->hand().at(11)));
    }
    else if (round == 7)
    {
        set_card(ui->Card1, king->hand().at(0));
        set_card(ui->Card2, king->hand().at(1));
        set_card(ui->Card3, king->hand().at(2));
        set_card(ui->Card4, king->hand().at(3));
        set_card(ui->Card5, king->hand().at(4));
        set_card(ui->Card6, king->hand().at(5));
        set_card(ui->Card7, king->hand().at(6));
        set_card(ui->Card8, king->hand().at(7));
        set_card(ui->Card9, king->hand().at(8));
        set_card(ui->Card10, king->hand().at(9));
        set_card(ui->Card11, king->hand().at(10));
        set_card(ui->Card12, king->hand().at(11));
        set_card(ui->Card13, king->hand().at(12));
        set_card(ui->Card14, king->hand().at(13));
        ui->BackCard_1->show();
        ui->BackCard_2->show();
        ui->BackCard_3->show();
        ui->BackCard_4->show();
        ui->BackCard_5->show();
        ui->BackCard_6->show();
        ui->BackCard_7->show();
        ui->BackCard_8->show();
        ui->BackCard_9->show();
        ui->BackCard_10->show();
        ui->BackCard_11->show();
        ui->BackCard_12->show();
        ui->BackCard_13->show();
        ui->BackCard_14->show();
        king_cards.insert(pair(ui->Card1, &king->hand().at(0)));
        king_cards.insert(pair(ui->Card2, &king->hand().at(1)));
        king_cards.insert(pair(ui->Card3, &king->hand().at(2)));
        king_cards.insert(pair(ui->Card4, &king->hand().at(3)));
        king_cards.insert(pair(ui->Card5, &king->hand().at(4)));
        king_cards.insert(pair(ui->Card6, &king->hand().at(5)));
        king_cards.insert(pair(ui->Card7, &king->hand().at(6)));
        king_cards.insert(pair(ui->Card8, &king->hand().at(7)));
        king_cards.insert(pair(ui->Card9, &king->hand().at(8)));
        king_cards.insert(pair(ui->Card10, &king->hand().at(9)));
        king_cards.insert(pair(ui->Card11, &king->hand().at(10)));
        king_cards.insert(pair(ui->Card12, &king->hand().at(11)));
        king_cards.insert(pair(ui->Card13, &king->hand().at(12)));
        king_cards.insert(pair(ui->Card14, &king->hand().at(13)));
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

    if (turn)
    {
        if (ui->KingCard->isHidden() && ui->OpponentCard->isHidden()) // for first hand play
        {
            set_card(ui->KingCard, *card->second);
            selected_card->hide();
            card->second->played_re() = true;
            card->second->save();
            k_card = card->second;
            turn = false;
            client->sendFile("card.txt", "play_card");
            box = new QMessageBox;
        }
        else if (ui->KingCard->isHidden() && !ui->OpponentCard->isHidden()) // for second player
        {
            if (card->second->compare(*op_card) == -1)
            {
                set_card(ui->KingCard, *card->second);
                selected_card->hide();
                card->second->played_re() = true;
                card->second->save();
                box = new QMessageBox(QMessageBox::Information, "Loosed", "You Loosed this Hand", QMessageBox::NoButton, this);
                box->setStyleSheet("border-image:none;");
                QTimer::singleShot(1000, box, &QMessageBox::accept);
                box->exec();
            }
            else if (card->second->compare(*op_card) == 0) // this rule is't working properly
            {
                auto it = std::find(king->hand().begin(), king->hand().end(), *op_card);
                if (it == king->hand().end())
                {
                    set_card(ui->KingCard, *card->second);
                    selected_card->hide();
                    card->second->played_re() = true;
                    card->second->save();
                    box = new QMessageBox(QMessageBox::Information, "Loosed", "You Loosed this Hand", QMessageBox::NoButton, this);
                    box->setStyleSheet("border-image:none;");
                    QTimer::singleShot(1000, box, &QMessageBox::accept);
                    box->exec();
                }
                else
                {
                    if (!it->played_re())
                    {
                        box = new QMessageBox(QMessageBox::Critical, "Wrong Choice", "Choose Wisly", QMessageBox::NoButton, this);
                        box->setStyleSheet("border-image:none;");
                        QTimer::singleShot(1000, box, &QMessageBox::accept);
                        box->exec();
                        return;
                    }
                    else
                    {
                        set_card(ui->KingCard, *card->second);
                        selected_card->hide();
                        card->second->played_re() = true;
                        card->second->save();
                        box = new QMessageBox(QMessageBox::Information, "Loose a Hand", "You Loosed this Hand", QMessageBox::NoButton, this);
                        box->setStyleSheet("border-image:none;");
                        QTimer::singleShot(1000, box, &QMessageBox::accept);
                        box->exec();
                    }
                }
            }
            else if (card->second->compare(*op_card) == 1)
            {
                set_card(ui->KingCard, *card->second);
                selected_card->hide();
                card->second->played_re() = true;
                card->second->save();
                // winning_card++;
                box = new QMessageBox(QMessageBox::Information, "Won", "You Won this Hand", QMessageBox::NoButton, this);
                box->setStyleSheet("border-image:none;");
                QTimer::singleShot(1000, box, &QMessageBox::accept);
                box->exec();
            }
            else if (card->second->compare(*op_card) == 2)
            {
                set_card(ui->KingCard, *card->second);
                selected_card->hide();
                card->second->played_re() = true;
                card->second->save();
                box = new QMessageBox(QMessageBox::Information, "Loosed", "You Loosed this Hand", QMessageBox::NoButton, this);
                box->setStyleSheet("border-image:none;");
                QTimer::singleShot(1000, box, &QMessageBox::accept);
                box->exec();
            }
            else
            {
                box = new QMessageBox(QMessageBox::Critical, "Wrong Choice", "Choose Wisly", QMessageBox::NoButton, this);
                box->setStyleSheet("border-image:none;");
                QTimer::singleShot(1000, box, &QMessageBox::accept);
                box->exec();
                return;
            }
            unset_card(ui->KingCard);
            unset_card(ui->OpponentCard);
            delete op_card;
            turn = false;
            // proces score here
            if (is_all_king_cards_played())
            {
                client->sendFile("card.txt", "next_round");
            }
            else
                client->sendFile("card.txt", "play_card");
        }
    }
    else
    {
        box = new QMessageBox(QMessageBox::Critical, "Turn", "It is not your turn", QMessageBox::NoButton, this);
        box->setStyleSheet("border-image:none;");
        QTimer::singleShot(1000, box, &QMessageBox::accept);
        box->exec();
    }
    delete box;
}

void Game::PlayCard()
{
    op_card = new Card;
    op_card->load();
    set_card(ui->OpponentCard, *op_card);
    turn = true;
    backCard_handling();
    if (!ui->KingCard->isHidden())
    {
        if (k_card->compare(*op_card) == -1)
        {
            box = new QMessageBox(QMessageBox::Information, "Loosed", "You Loosed this Hand", QMessageBox::NoButton, this);
            box->setStyleSheet("border-image:none;");
            QTimer::singleShot(1000, box, &QMessageBox::accept);
            box->exec();
        }
        else if (k_card->compare(*op_card) == 0) // should check
        {
            // winning_card++;
            box = new QMessageBox(QMessageBox::Information, "Won", "You Won this Hand", QMessageBox::NoButton, this);
            box->setStyleSheet("border-image:none;");
            QTimer::singleShot(1000, box, &QMessageBox::accept);
            box->exec();
        }

        else if (k_card->compare(*op_card) == 1)
        {
            // winning_card++;
            box = new QMessageBox(QMessageBox::Information, "Won", "You Won this Hand", QMessageBox::NoButton, this);
            box->setStyleSheet("border-image:none;");
            QTimer::singleShot(1000, box, &QMessageBox::accept);
            box->exec();
        }
        else if (k_card->compare(*op_card) == 2)
        {
            // winning_card++;
            box = new QMessageBox(QMessageBox::Information, "Won", "You Won this Hand", QMessageBox::NoButton, this);
            box->setStyleSheet("border-image:none;");
            QTimer::singleShot(1000, box, &QMessageBox::accept);
            box->exec();
        }
        unset_card(ui->KingCard);
        unset_card(ui->OpponentCard);
        delete op_card;
        delete box;
        // proces score here
        if (is_all_king_cards_played())
        {
            client->sendSignal("next_round");
        }
    }
}

void Game::Pause()
{
    box = new QMessageBox;
    box->setText("Paused");
    // box->setStandardButtons(QMessageBox::NoButton);
    box->setWindowIcon(this->windowIcon());
    box->exec();
}

void Game::Resume()
{
    box->close();
    delete box;
}

void Game::on_Stop_clicked()
{
    int static num = 0;
    if (num < 2)
    {
        client->sendSignal("pause");
        box = new QMessageBox;
        box->setText("This closes in 20 seconds");
        box->addButton("Resume", QMessageBox::ButtonRole::AcceptRole);
        box->setWindowIcon(this->windowIcon());
        connect(box, &QMessageBox::accepted,
                [&]()
                {
                    client->sendSignal("resume");
                });

        int cnt = 20;
        QTimer cntDown;

        connect(&cntDown, &QTimer::timeout,
                [&]()
                {
                    if (cnt < 0)
                    {
                        cntDown.stop();
                        box->accept();
                    }
                    else
                    {
                        box->setText(QString("This closes in %1 seconds").arg(cnt));
                        cnt--;
                    }
                });
        cntDown.start(1000);
        box->exec();
        num++;
        delete box;
    }
}

void Game::on_Exit_clicked()
{
}

void Game::backCard_handling()
{
    if (!ui->BackCard_1->isHidden())
    {
        ui->BackCard_1->hide();
        return;
    }
    else if (!ui->BackCard_2->isHidden())
    {
        ui->BackCard_2->hide();
        return;
    }
    else if (!ui->BackCard_3->isHidden())
    {
        ui->BackCard_3->hide();
        return;
    }
    else if (!ui->BackCard_4->isHidden())
    {
        ui->BackCard_4->hide();
        return;
    }
    else if (!ui->BackCard_5->isHidden())
    {
        ui->BackCard_5->hide();
        return;
    }
    else if (!ui->BackCard_6->isHidden())
    {
        ui->BackCard_6->hide();
        return;
    }
    else if (!ui->BackCard_7->isHidden())
    {
        ui->BackCard_7->hide();
        return;
    }
    else if (!ui->BackCard_8->isHidden())
    {
        ui->BackCard_8->hide();
        return;
    }
    else if (!ui->BackCard_9->isHidden())
    {
        ui->BackCard_9->hide();
        return;
    }
    else if (!ui->BackCard_10->isHidden())
    {
        ui->BackCard_10->hide();
        return;
    }
    else if (!ui->BackCard_11->isHidden())
    {
        ui->BackCard_11->hide();
        return;
    }
    else if (!ui->BackCard_12->isHidden())
    {
        ui->BackCard_12->hide();
        return;
    }
    else if (!ui->BackCard_13->isHidden())
    {
        ui->BackCard_13->hide();
        return;
    }
    else if (!ui->BackCard_14->isHidden())
    {
        ui->BackCard_14->hide();
        return;
    }
}

bool Game::is_all_king_cards_played()
{
    bool flag = true;
    for (auto &&i : king->hand())
    {
        if (!i.played_re())
            flag = false;
    }
    return flag;
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
