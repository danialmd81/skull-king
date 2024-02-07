#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) : QDialog(parent), ui(new Ui::Login)
{
    player = new QMediaPlayer;
    output = new QAudioOutput;
    player->setAudioOutput(output);
    player->setSource(QUrl("qrc:/Resource/Audio/pirate-of-caribbean.mp3"));
    player->setLoops(QMediaPlayer::Infinite);
    output->setVolume(30);
    player->play();
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
    delete player;
    delete output;
}

void Login::on_SginIn_clicked()
{
    if (ui->username->text().isEmpty() || ui->password->text().isEmpty())
    {
        QMessageBox error(QMessageBox::Critical, "Login", "Field(s) is(are) empty");
        error.setWindowIcon(this->windowIcon());
        error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
        error.exec();
    }
    else
    {
        ifstream file;
        file.open(ui->username->text().toStdString() + ".txt");
        if (file)
        {
            king = new King(file);
            file.close();
            if (king->password() == ui->password->text().toStdString())
            {
                this->hide();
                menu = new Menu(king);
                menu->setModal(true);
                menu->showFullScreen();
                connect(menu, &QDialog::accepted, this, &menu_Slot);
            }
        }
        else
        {
            QMessageBox error(QMessageBox::Critical, "Login", "Username or Password is incorrect");
            error.setWindowIcon(this->windowIcon());
            error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
            error.exec();
        }
    }
}

void Login::menu_Slot()
{
    this->showFullScreen();
    delete menu;
}

void Login::on_SignUp_clicked()
{
    signup = new SignUp(this);
    signup->exec();
}

void Login::on_ShowPassword_stateChanged(int arg1)
{
    if (arg1 == 2)
        ui->password->setEchoMode(QLineEdit::Normal);
    else
        ui->password->setEchoMode(QLineEdit::Password);
}

void Login::on_ForgotPasswprd_clicked()
{
    forgot = new ForgotPassword(this);
    forgot->exec();
}

void Login::on_Exit_clicked()
{
    this->done(QDialog::Rejected);
}
