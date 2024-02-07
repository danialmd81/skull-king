#include "forgotpassword.h"
#include "ui_forgotpassword.h"

ForgotPassword::ForgotPassword(QWidget *parent) : QDialog(parent), ui(new Ui::ForgotPassword)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_Enter_clicked()
{
    if (ui->Username->text().isEmpty() || ui->Phone->text().isEmpty() || ui->NewPassword->text().isEmpty())
    {
        QMessageBox error(QMessageBox::Critical, "Forget Password", "Field(s) is(are) empty!");
        error.setWindowIcon(this->windowIcon());

        error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
        error.exec();
    }
    else
    {
        ifstream file;
        QString username = ui->Username->text();
        file.open((username + ".txt").toStdString().c_str(), ios::in);
        if (file)
        {
            King king(file);
            file.close();
            QString phone = ui->Phone->text();
            if (king.phone() == phone.toStdString().c_str())
            {
                king.password() = ui->NewPassword->text().toStdString();
                king.save();
                this->done(QDialog::Accepted);
            }
            else
            {
                QMessageBox error(QMessageBox::Critical, "Forget Password", "Phone number is incorrect!");
                error.setWindowIcon(this->windowIcon());
                error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";\";color: rgb(255, 0, 0);");
                error.exec();
            }
        }

        else
        {
            QMessageBox error(QMessageBox::Critical, "Forget Password", "This username do not exist!");
            error.setWindowIcon(this->windowIcon());
            error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";\";color: rgb(255, 0, 0);");
            error.exec();
        }
    }
}

void ForgotPassword::on_Cancel_clicked()
{
    this->done(QDialog::Rejected);
}
