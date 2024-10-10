#ifndef TCPLINKCLIENT_H
#define TCPLINKCLIENT_H

#include <QObject>
#include <QTcpSocket>
class TCPLinkClient : public QObject
{
    Q_OBJECT
public:
    TCPLinkClient(QObject *parent = nullptr);
    Q_PROPERTY(QStringList serverMessages READ serverMessages NOTIFY serverMessagesChanged)
    Q_PROPERTY(QStringList clientMessages READ clientMessages NOTIFY clientMessagesChanged)

    QStringList serverMessages (){ return _serverMessages; }
    QStringList clientMessages (){ return _clientMessages; }

    Q_INVOKABLE void sendNotification(const QString message);


    void setMessages(QString msg);
    void receivedMessage(QString msg);

public slots:
    void onConnected();
    void onReadReady();
    void onDisconnected();

signals:
    void serverMessagesChanged();
    void clientMessagesChanged();
    void messagesChanged();

private:
    QStringList _serverMessages;
    QStringList _clientMessages ;
    QTcpSocket* _socket;
};

#endif // TCPLINKCLIENT_H
