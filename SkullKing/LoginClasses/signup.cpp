#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) : QDialog(parent), ui(new Ui::SignUp)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_cancel_clicked()
{
    this->done(QDialog::Rejected);
}

void SignUp::on_save_clicked()
{
    if (ui->Name->text().isEmpty() || ui->Username->text().isEmpty() || ui->Password->text().isEmpty() || ui->Phone->text().isEmpty() || ui->Address->text().isEmpty())
    {
        QMessageBox error(QMessageBox::Critical, "Field", "Fill all empty Field(s)");
        error.setWindowIcon(this->windowIcon());
        error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
        error.exec();
    }
    else
    {
        if (ui->Password->text().size() < 8)
        {
            QMessageBox error(QMessageBox::Critical, "Password", "Password is short");
            error.setWindowIcon(this->windowIcon());
            error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
            error.exec();
        }
        else if (ui->Phone->text().size() != 11 && ui->Phone->text().size() != 13)
        {
            QMessageBox error(QMessageBox::Critical, "Phone", "Phone number is wrong");
            error.setWindowIcon(this->windowIcon());
            error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
            error.exec();
        }
        else
        {
            King king(ui->Name->text().toStdString(), ui->Username->text().toStdString(), ui->Password->text().toStdString(), ui->Phone->text().toStdString(), ui->Address->text().toStdString());

            if (filesystem::exists(king.username() + ".txt"))
            {
                QMessageBox error(QMessageBox::Critical, "Username", "Username had been taken by another king");
                error.setWindowIcon(this->windowIcon());
                error.setStyleSheet("font: italic 15pt \"Monotype Corsiva\";color: rgb(255, 0, 0);");
                error.exec();
            }
            else
            {
                king.save();
                this->done(QDialog::Accepted);
            }
        }
    }
}
