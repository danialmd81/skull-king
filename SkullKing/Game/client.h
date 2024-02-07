#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
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
    void sendSignal(QString signal);
    void sendFile(QString filePath, QString signal);

signals:
    void newSignal(QString);
    void cancel(std::string);
    void connected_to_server();
    void oppnent_king(std::string filepath);
    void other_king_of_client(QString);
    void kings_ready();

    void start_game();
    void start_round();
    void play_card();
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
