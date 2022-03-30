#include "chatserver.h"
#include "serverworker.h"
#include <QThread>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QJsonValue>
#include <QTimer>
#include<QDebug>
ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent){}
void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Connected"));
}
void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}
void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker == exclude && !message.contains("users") )
            continue;
        sendJson(worker, message);
    }
}
void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->userName().isEmpty())
         jsonFromLoggedOut(sender, doc);
    else
         jsonFromLoggedIn(sender, doc);
}
void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
    if (!userName.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
        disconnectedMessage[QStringLiteral("username")] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + QLatin1String(" disconnected"));
    }
    sender->deleteLater();
    //implement Online Users that for update users when any user disconnecting the serve----------------
        QJsonArray array = {};
        for(int i=0;i<m_clients.size();i++)
          array.append(QString(m_clients.at(i)->userName()));

        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("online");
        message[QStringLiteral("users")] = array;
        message[QStringLiteral("sender")] = sender->userName();
        broadcast(message, sender);
}

void ChatServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
}

void ChatServer::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void ChatServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (ServerWorker *worker : qAsConst(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("success")] = false;
            message[QStringLiteral("reason")] = QStringLiteral("duplicate username");
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);
    QJsonObject successMessage;
    successMessage[QStringLiteral("type")] = QStringLiteral("login");
    successMessage[QStringLiteral("success")] = true;
    sendJson(sender, successMessage);
    QJsonObject connectedMessage;
    connectedMessage[QStringLiteral("type")] = QStringLiteral("newuser");
    connectedMessage[QStringLiteral("username")] = newUserName;
    broadcast(connectedMessage, sender);

    //implement Online Users----------------

        QJsonArray array = {};
        for(int i=0;i<m_clients.size();i++)
          array.append(QString(m_clients.at(i)->userName()));
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("online");
        message[QStringLiteral("users")] = array;
        message[QStringLiteral("sender")] = sender->userName();
        broadcast(message, sender);
}

void ChatServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;

    const QJsonValue textVal = docObj.value(QLatin1String("text"));
    if (textVal.isNull() || !textVal.isString())
        return;
    const QString text = textVal.toString().trimmed();
    if (text.isEmpty())
        return;
    QJsonObject message;
    //qDebug()<<"11111111";
    if(typeVal.toString().compare(QLatin1String("private"), Qt::CaseInsensitive) == 0){
         //qDebug()<<"111111222222";
         message[QStringLiteral("type")] = QLatin1String("private");
         message[QStringLiteral("text")] = text;
         message[QStringLiteral("sender")] = sender->userName();
         message[QStringLiteral("reciever")] = docObj.value(QLatin1String("reciever"));

         for(int i=0;i<m_clients.size();i++)
            if(m_clients.at(i)->userName()== docObj.value(QLatin1String("reciever")).toString().trimmed())
                   sendJson(m_clients.at(i),message);

    }
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0)
    {
         message[QStringLiteral("type")] = QLatin1String("message");
         message[QStringLiteral("text")] = text;
         message[QStringLiteral("sender")] = sender->userName();
         broadcast(message,sender);
    }

}

