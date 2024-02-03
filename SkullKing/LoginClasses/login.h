#ifndef LOGIN_H
#define LOGIN_H

#include "MyClasses/king.h"
#include "signup.h"
#include "forgotpassword.h"
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
    King *king_re();

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
    ForgotPassword *forgot;
    King *king;
};

#endif // LOGIN_H
