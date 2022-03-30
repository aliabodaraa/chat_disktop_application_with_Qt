#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
class QJsonObject;
class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    /// @brief represents name of current user name 
    /// @return name of current user
    QString userName() const;
    /// @brief set the user name 
    /// @param userName name of current user
    void setUserName(const QString &userName);
    /// @brief read server the mssg to client
    /// @param jsonData json data object the the server will read it
    void sendJson(const QJsonObject &jsonData);
    /// @brief get priate user name
    /// @return 
    QString getUserName();
signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
public slots:
    /// @brief disconnect the connection with client
    void disconnectFromClient();
private slots:
    void receiveJson();
private:
    QTcpSocket *m_serverSocket;
    QString m_userName;
};

#endif // SERVERWORKER_H
