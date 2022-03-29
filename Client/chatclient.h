#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>

class QHostAddress;
class QJsonDocument;
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
    QString currentNameUser;
    void sendMessageToSelectedUser(const QString &msg,const QString &targetUserName );
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    /// sends a message to the connected user
    void sendMessage(const QString &text);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void onlineUsers(const QJsonArray &username);
    void SignalReceiveMessageFromSpecificUser(QString senderVal,QString textVal);//for chat with one user
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
};

#endif // CHATCLIENT_H
