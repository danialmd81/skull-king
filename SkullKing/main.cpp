#include "LoginClasses/login.h"
#include "Game/game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Login login;
    login.showFullScreen();
    // Game game;
    // game.showFullScreen();
    return app.exec();
}
