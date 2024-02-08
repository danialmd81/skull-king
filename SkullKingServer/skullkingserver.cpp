#include "skullkingserver.h"
#include "ui_skullkingserver.h"

using namespace std;

SkullKingServer::SkullKingServer(QWidget *parent) : QDialog(parent), ui(new Ui::SkullKingServer)
{
    ui->setupUi(this);
    ui->Ip->hide();
    ui->Port->hide();
    ui->label_3->hide();
    ui->label->hide();
}

SkullKingServer::~SkullKingServer()
{

    for (auto &&i : clients)
    {
        i.first->close();
        i.first->deleteLater();
    }
    clients.clear();
    server->close();
    server->deleteLater();
    delete ui;
}

void SkullKingServer::on_Ok_clicked()
{
    client_number = ui->number_of_players->value();
    ui->Ok->hide();
    ui->Ip->show();
    ui->Port->show();
    ui->label_3->show();
    ui->label->show();
    ui->player_number->setText("Player Connected to Server:0");
    ui->number_of_players->hide();
    server = new QTcpServer();
    if (server->listen(QHostAddress::LocalHost, 56000))
    {
        ui->Ip->setText(server->serverAddress().toString());
        ui->Port->setText(to_string(server->serverPort()).c_str());
        connect(server, &QTcpServer::newConnection, this, &SkullKingServer::newConnection);
    }
    else
    {
        QMessageBox::critical(this, "QTCPServer",
                              QString("Unable to start the server: %1.").arg(server->errorString()));
        exit;
    }
}

void SkullKingServer::newConnection()
{
    while (server->hasPendingConnections() && clients.size() < client_number)
    {
        appendToSocketList(server->nextPendingConnection());
    }
}

void SkullKingServer::appendToSocketList(QTcpSocket *socket)
{
    if (clients.find(socket) == clients.end())
    {
        clients.insert(pair(socket, King()));
        ui->player_number->setText(("Player Connected to Server:" + to_string(clients.size())).c_str());
        connect(socket, &QTcpSocket::readyRead, this, &SkullKingServer::readSocket);
        connect(socket, &QTcpSocket::disconnected, this, &SkullKingServer::discardSocket);
        connect(socket, &QTcpSocket::errorOccurred, this, &SkullKingServer::displayError);
    }
}

void SkullKingServer::readSocket()
{
    QTcpSocket *socket = reinterpret_cast<QTcpSocket *>(sender());
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_5);
    socketStream.startTransaction();
    socketStream >> buffer;
    if (!socketStream.commitTransaction())
    {
        return;
    }
    QString header = buffer.mid(0, 128);
    QString fileType = header.split(",")[0].split(":")[1];
    buffer = buffer.mid(128);
    if (fileType == "file")
    {
        QString fileName = header.split(",")[1].split(":")[1];
        QString ext = fileName.split(".")[1];
        QString signal = header.split(",")[2].split(":")[1];
        QString size = header.split(",")[3].split(":")[1].split(";")[0];
        QString filePath = fileName;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(buffer);
            file.close();
            if (signal == "king")
            {
                static int num = 0;
                King king;
                king.load(fileName.toStdString());
                clients.at(socket) = king;
                num++;
                if (num == client_number)
                {
                    this->hide();
                    start_game();
                }
            }
            else if (signal == "play_card")
            {
                // play_card(socket);
            }
            else if (signal == "round_ended")
            {
                ifstream file;
                file.open("round.txt", ios::in);
                // file >> round;
                // file.close();
                // round++;
                // start_round(socket, round);
            }
        }
        else
            QMessageBox::critical(this, "QTCPServer", "An error occurred while trying to write the attachment.");
    }
    else if (fileType == "signal")
    {
        int round_ended_times = 0;
        QString signal(buffer.toStdString().c_str());
        if (signal == "start_game_ended")
        {
            start_round(1);
        }
    }
}

void SkullKingServer::discardSocket()
{
    QTcpSocket *socket = reinterpret_cast<QTcpSocket *>(sender());
    auto it = clients.find(socket);
    if (it != clients.end())
    {
        clients.erase(it);
    }
    socket->deleteLater();
}

void SkullKingServer::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "QTCPServer",
                                 "The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "QTCPServer",
                                 "The connection was refused by the peer. Make sure QTCPServer is running, and check "
                                 "that the host name and port settings are correct.");
        break;
    default:
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        QMessageBox::information(this, "QTCPServer",
                                 QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}

void SkullKingServer::sendSignal(QTcpSocket *socket, QString signal)
{
    if (socket)
    {
        if (socket->isOpen())
        {
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_6_5);
            QByteArray header;
            header.prepend(QString("fileType:signal,fileName:null,fileSize:%1;").arg(signal.size()).toUtf8());
            header.resize(128);
            QByteArray byteArray = signal.toUtf8();
            byteArray.prepend(header);
            socketStream.setVersion(QDataStream::Qt_6_5);
            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this, "QTCPServer", "Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this, "QTCPServer", "Not connected");
}

void SkullKingServer::sendFile(QTcpSocket *socket, QString filePath, QString signal)
{
    if (socket)
    {
        if (socket->isOpen())
        {
            socket->setReadBufferSize(0);
            QFile m_file(filePath);
            if (m_file.open(QIODevice::ReadOnly))
            {
                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());
                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_6_5);
                QByteArray header;
                header.prepend(QString("fileType:file,fileName:%1,signal:%2,fileSize:%3;")
                                   .arg(fileName)
                                   .arg(signal)
                                   .arg(m_file.size())
                                   .toUtf8());
                header.resize(128);
                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);
                socketStream << byteArray;
            }
            else
                QMessageBox::critical(this, "QTCPClient", "Couldn't open the attachment!");
        }
        else
            QMessageBox::critical(this, "QTCPServer", "Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this, "QTCPServer", "Not connected");
}

void SkullKingServer::start_game()
{
    Card starter_cards[clients.size()];
    ofstream file;
    file.open("start.txt", ios::out | ios::trunc);
    for (auto &&i : clients)
    {
        i.second.starter_card() = deck.set_starter();
        file << i.second.username() << " " << i.second.starter_card() << " ";
    }
    file << "end.";
    file.close();
    for (auto &&i : clients)
    {
        sendFile(i.first, "start.txt", "start_game");
    }
    deck.reset();
}

void SkullKingServer::start_round(int r)
{
    for (auto &&king : clients)
    {
        for (int i = 0; i < 2 * r; i++)
        {
            king.second.hand().push_back(deck.random());
        }
        king.second.save();
        sendFile(king.first, king.second.filePath().c_str(), "start_round");
    }
    deck.reset();
}

// void SkullKingServer::play_card(QTcpSocket *qts)
// {
// auto it = clients.find(qts);
// for (auto &&i : clients)
// {
//     if (i.first != it->first)
//     {
//         sendFile(i.first, "card.txt", "play_card");
//     }
// }
// }
