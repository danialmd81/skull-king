#ifndef LOGIN_H
#define LOGIN_H

#include "MyClasses/king.h"
#include "Menu/menu.h"
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

private slots:
    void on_SginIn_clicked();
    void on_SignUp_clicked();
    void on_ShowPassword_stateChanged(int arg1);
    void on_ForgotPasswprd_clicked();
    void on_Exit_clicked();
    void menu_Slot();

private:
    Ui::Login *ui;
    QMediaPlayer *player;
    QAudioOutput *output;
    SignUp *signup;
    ForgotPassword *forgot;
    King *king;
    Menu *menu;
};

#endif // LOGIN_H
