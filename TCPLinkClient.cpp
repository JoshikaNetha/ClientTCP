#include "TCPLinkClient.h"

TCPLinkClient::TCPLinkClient(QObject *parent)
    : QObject{parent}
    ,_socket(new QTcpSocket(this))
{
    _socket->connectToHost("127.0.0.1",12345);
    connect(_socket,&QTcpSocket::connected,this,&TCPLinkClient::onConnected);
    // connect(_socket, &QTcpSocket::connected, [this]() {
    //     this->sendNotification("Hello, Server!");  // Send a message to the server
    // });
    connect(_socket, &QTcpSocket::readyRead, this, &TCPLinkClient::onReadReady);
    connect(_socket, &QTcpSocket::disconnected, this, &TCPLinkClient::onDisconnected);
    connect(_socket, &QTcpSocket::errorOccurred, [](QAbstractSocket::SocketError socketError) {
        qDebug() << "Socket error:" << socketError;
    });
}

void TCPLinkClient::sendNotification(const QString message)
{
    if (_socket->state() == QAbstractSocket::ConnectedState) {
        _socket->write(message.toUtf8());
        setMessages(message);
    } else {
        qDebug() << "Not connected to server.";
    }
}

void TCPLinkClient::setMessages(QString msg)
{
    _clientMessages.append(msg);
    emit clientMessagesChanged();
}

void TCPLinkClient::receivedMessage(QString msg)
{
    _serverMessages.append(msg);
    emit serverMessagesChanged();
}

void TCPLinkClient::onConnected()
{
    qDebug()<<"Connnected";
}

void TCPLinkClient::onReadReady()
{
    qDebug()<<"Read ready";
    QByteArray data = _socket->readAll();
    qDebug() << "Received from server:" << data;
    receivedMessage(data);
    // setMessages(data);
}

void TCPLinkClient::onDisconnected()
{
    qDebug() << "Disconnected from server.";
}

