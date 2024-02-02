#include "LoginClasses/login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.showFullScreen();
    return a.exec();
}
