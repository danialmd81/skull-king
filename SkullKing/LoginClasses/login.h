#ifndef LOGIN_H
#define LOGIN_H

#include "MyClasses/king.h"
#include "LoginClasses/signup.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QMessageBox>
#include <QDialog>

namespace Ui
{
    class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login();

private slots:
    void on_SginIn_clicked();
    void on_SignUp_clicked();
    void on_ShowPassword_stateChanged(int arg1);
    void on_ForgotPasswprd_clicked();
    void on_Exit_clicked();

private:
    Ui::Login *ui;
    QMediaPlayer *player;
    QAudioOutput *output;
    SignUp *signup;
};

#endif // LOGIN_H
