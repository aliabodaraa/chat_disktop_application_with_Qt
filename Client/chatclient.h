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
    /// @brief constructor for class ChatClient
    explicit ChatClient(QObject *parent = nullptr);
    /// @brief represent current user name
    QString currentNameUser;
    /// @brief represents send nessage to specific user
    /// @param represents the content of message
    /// @param targetUserName represents name user that i want to chat with you after i select the latter from listWidget 
    void sendMessageToSelectedUser(const QString &msg,const QString &targetUserName );
public slots:
    /// @brief represents connecting the server
    void connectToServer(const QHostAddress &address, quint16 port);
    /// @brief represents that the user loggedIn to the server
    /// @param userName 
    void login(const QString &userName);
    /// sends a message to the connected user
    void sendMessage(const QString &text);
    /// @brief represents that the user has missed connecting to the server
    void disconnectFromHost();
private slots:
    /// @brief it responsible for read some data from server side and convert document Json to json variable 
    void onReadyRead();
signals:
    /// @brief represents that the user connecting to the server
    void connected();
    /// @brief represents that the user loggedIn to the server
    void loggedIn();
    /// @brief represents that the user doesn't enter your name or when he enter name has already existed in app
    /// @param clarify reason either empty name or duplicated name
    void loginError(const QString &reason);
    /// @brief represents that the user has missed connecting to the server
    void disconnected();
    /// @brief represents that the user receive a massage from server
    /// @param sender name of user
    /// @param text represents received user's message
    void messageReceived(const QString &sender, const QString &text);
    /// @brief represents failing in connect sockets such as NetworkError ..
    /// @param text represents type of error connecting sockets
    void error(QAbstractSocket::SocketError socketError);
    /// @brief represents that the user has already joined to the App
    /// @param username represents name of user
    void userJoined(const QString &username);
    /// @brief represents that the user has already left to the App
    /// @param username represents name of user
    void userLeft(const QString &username);
    /// @brief represents that the user is online to the App
    /// @param users represents names of users that are online
    void onlineUsers(const QJsonArray &users);
    /// @brief represents communication between two users
    /// @param senderVal name of user that start writting messages to the another
    /// @param textVal represents content of message
    void SignalReceiveMessageFromSpecificUser(QString senderVal,QString textVal);//for chat with one user
private:
    /// @brief represents pointer to client socket
    QTcpSocket *m_clientSocket;
    /// @brief represents status of user maybe he is logging in or not
    bool m_loggedIn;
    /// @brief represents that the client receive a json object from server
    /// @param doc represents received json object
    void jsonReceived(const QJsonObject &doc);
};

#endif // CHATCLIENT_H
