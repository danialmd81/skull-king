#include "LoginClasses/login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Login login;
    login.showFullScreen();
    if (login.result() == QDialog::Accepted)
    {
        // open menu for king and pass king to its constructor
    }

    return app.exec();
}
