#ifndef CLIENT_H
#define CLIENT_H

#include <QFile>
#include <QFileInfo>
#include <QHostAddress>
#include <QMessageBox>
#include <QString>
#include <QTcpSocket>
#include <QDialog>
#include <string>

namespace Ui
{
    class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
    bool sendSignal(QString signal);
    bool sendFile(QString filePath, QString signal);

signals:
    void newSignal(QString);

    void connected_to_server();
    void start_game(std::string filepath);
    void start_round();
    void play_card();
    void pause();
    void resume();
    void end_game();

private slots:
    void on_Connect_clicked();
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};

#endif // CLIENT_H
