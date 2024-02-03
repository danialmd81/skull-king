#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QDialog(parent), ui(new Ui::Login)
{
    player = new QMediaPlayer;
    output = new QAudioOutput;
    player->setAudioOutput(output);
    player->setSource(QUrl("qrc:/Resource/Audio/pirate-of-caribbean.mp3"));
    player->setLoops(-1);
    output->setVolume(30);
    player->play();
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
    delete player;
    delete output;
    delete signup;
}

void Login::on_SginIn_clicked()
{
    if (ui->username->text().isEmpty() || ui->password->text().isEmpty())
    {
        QMessageBox error(QMessageBox::Critical, "Login", "Fields are empty");
        error.setWindowIcon(this->windowIcon());
        error.setStyleSheet("font: 700 12pt \" Cascadia Mono \";color: rgb(255, 0, 0);");
        error.exec();
    }
    else
    {
        ifstream file;
        file.open(ui->username->text().toStdString() + ".txt");
        if (file)
        {
            King king;
            file >> king;
            file.close();
            if (king.password() == ui->password->text().toStdString())
            {
                ui->username->clear();
                ui->password->clear();
                this->accept();
            }
        }
        else
        {
            QMessageBox error(QMessageBox::Critical, "Login", "Username or Password is incorrect");
            error.setWindowIcon(this->windowIcon());
            error.setStyleSheet("font: 700 12pt \" Cascadia Mono \";color: rgb(255, 0, 0);");
            error.exec();
        }
    }
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
    
}

void Login::on_Exit_clicked()
{
    this->reject();
}
