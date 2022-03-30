#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QVector>

class ServerWorker;
class ChatServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatServer)
public:
    explicit ChatServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void logMessage(const QString &msg);
public slots:
    void stopServer();
private slots:
    /// @brief it represent send the message for all user as broadcast send
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    /// @brief it represent send server the message from depending on type of msg
    /// @param sender sender the mssg
    /// @param doc represents the data that will send via server
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
    void userError(ServerWorker *sender);
private:
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    /// @brief send msg from server it use in jsonReceived methos
    /// @param destination target receiver
    /// @param message represents the json variable that will send via server
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    /// @brief it contains all users in app
    QVector<ServerWorker *> m_clients;
};

#endif // CHATSERVER_H
