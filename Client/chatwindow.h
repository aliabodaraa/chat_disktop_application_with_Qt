#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include "chatoneuser.h"

class ChatClient;
class QStandardItemModel;
namespace Ui { class ChatWindow; }
class ChatWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    Ui::ChatWindow *ui;
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;
    QVector<QString> privateChats;

signals:
    void signalSendMsgToDialog(QString sender, QString text);//for chat with one user

private slots:
    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
    void reciveOnlineUsers(const QJsonArray &users);
    void receiveMessageFromSpecificUser(QString senderVal,QString textVal);//for chat with one user
    void on_ButtonChatOneUser_clicked();//for chat with one user
};

#endif // CHATWINDOW_H
