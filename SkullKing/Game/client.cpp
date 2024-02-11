#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) : QDialog{parent}, ui(new Ui::Client)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readSocket);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::displayError);
    connect(socket, &QTcpSocket::disconnected, this, &Client::discardSocket);
    ui->Status->setText("Waiting for King input.");
}

Client::~Client()
{
    delete socket;
    delete ui;
}

void Client::on_Connect_clicked()
{
    // if (ui->Ip->text().isEmpty() || ui->Port->text().isEmpty())
    // {
    //     QMessageBox::critical(this, "Fields", "Fill the empty fields");
    // }
    // else
    // {
    // QHostAddress address(ui->Ip->text());
    // socket->connectToHost(address, ui->Port->text().toInt());
    socket->connectToHost(QHostAddress::LocalHost, 56000);
    if (socket->waitForConnected(3000))
    {
        QMessageBox::information(this, "Connected", "Connected to Server");
        ui->Status->setText("Waiting for Opponent(s) Connection");
        ui->Connect->hide();
        emit connected_to_server();
        return;
    }
    else
    {
        QMessageBox::critical(this, "QTCPClient",
                              QString("The following error occurred: %1.").arg(socket->errorString()));
    }
    // }
}

void Client::readSocket()
{
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
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            file.write(buffer);
            file.close();
            if (signal == "start_game")
            {
                this->hide();
                emit start_game(filePath.toStdString());
                return;
            }
            else if (signal == "start_round")
            {
                emit start_round();
                return;
            }
            else if (signal == "play_card")
            {
                emit play_card();
                return;
            }
        }
        else
            QMessageBox::critical(this, "QTCPServer", "An error occurred while trying to write the attachment.");
    }
    else if (fileType == "signal")
    {
        QString signal(buffer.toStdString().c_str());
        if (signal == "pause")
        {
            emit pause();
            return;
        }
        else if (signal == "resume")
        {
            emit resume();
            return;
        }
    }
}

void Client::discardSocket() // Okay
{
    socket->deleteLater();
    socket = nullptr;
}

void Client::displayError(QAbstractSocket::SocketError socketError) // Okay
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "QTCPClient",
                                 "The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "QTCPClient",
                                 "The connection was refused by the peer. Make sure QTCPServer is running, and check "
                                 "that the host name and port settings are correct.");
        break;
    default:
        QMessageBox::information(this, "QTCPClient",
                                 QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}

bool Client::sendSignal(QString signal) // Okay
{
    if (socket)
    {
        if (socket->isOpen())
        {
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_6_5);
            QByteArray header;
            header.prepend(QString("Type:signal,Name:null,Size:%1;").arg(signal.size()).toUtf8());
            header.resize(128);
            QByteArray byteArray = signal.toUtf8();
            byteArray.prepend(header);
            socketStream << byteArray;
            return true;
        }
        else
        {
            // QMessageBox::critical(this, "QTCPClient", "Socket doesn't seem to be opened");
            return false;
        }
    }
    else
    {
        // QMessageBox::critical(this, "QTCPClient", "Not connected");
        return false;
    }
}

bool Client::sendFile(QString filePath, QString signal) // Okay
{
    if (socket)
    {
        if (socket->isOpen())
        {
            if (filePath.isEmpty())
            {
                // QMessageBox::critical(this, "QTCPClient", "You haven't selected any attachment!");
                return false;
            }
            QFile m_file(filePath);
            if (m_file.open(QIODevice::ReadOnly))
            {
                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_6_5);
                QByteArray header;
                header.prepend(QString("Type:file,Name:%1,signal:%2,Size:%3;").arg(fileName).arg(signal).arg(m_file.size()).toUtf8());
                header.resize(128);
                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);
                socketStream.setVersion(QDataStream::Qt_6_5);
                socketStream << byteArray;
                return true;
            }
            else
            {
                // QMessageBox::critical(this, "QTCPClient", "Attachment is not readable!");
                return false;
            }
        }
        else
        {
            // QMessageBox::critical(this, "QTCPClient", "Socket doesn't seem to be opened");
            return false;
        }
    }
    else
    {
        // QMessageBox::critical(this, "QTCPClient", "Not connected");
        return false;
    }
}
