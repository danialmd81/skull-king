#include "menu.h"
#include "ui_menu.h"

Menu::Menu(King *king, QWidget *parent) : QDialog(parent), ui(new Ui::Menu)
{
    this->king = king;
    ui->setupUi(this);
}

Menu::~Menu()
{

    delete ui;
}

void Menu::on_Logout_clicked()
{
    this->done(QDialog::Accepted);
}
void Menu::on_Exit_clicked()
{
    this->done(QDialog::Rejected);
}

void Menu::on_StartGame_clicked()
{
    this->hide();
    game = new Game(king);
    connect(game, Game::finished, this, Menu::game_slot);
}

void Menu::game_slot()
{
    this->showFullScreen();
    delete game;
}

void Menu::on_History_clicked()
{
}

void Menu::on_ChangeProfile_clicked()
{
}
