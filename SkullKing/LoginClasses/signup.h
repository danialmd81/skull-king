#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <filesystem>
#include <fstream>
#include "MyClasses/king.h"

namespace Ui
{
    class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_cancel_clicked();
    void on_save_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
