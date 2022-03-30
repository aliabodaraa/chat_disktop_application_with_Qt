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
    /// @brief the instructor of ChatWindow class
    /// @param represents the pointer from QWidget that is the parent of class ChatWindow
    explicit ChatWindow(QWidget *parent = nullptr);
    /// @brief the destructor of ChatWindow class
    ~ChatWindow();
private:
    /// @brief represents pointer from ChatWindow class
    Ui::ChatWindow *ui;
    /// @brief represents pointer from ChatClient class
    ChatClient *m_chatClient;
    /// @brief 
    QStandardItemModel *m_chatModel;
    /// @brief represents current user name
    QString m_lastUserName;
    /// @brief represents a vector of users that any user can start chatting with any user in this vector
    QVector<QString> privateChats;

signals:
    /// @brief represents signal to trigger sending message to spesific user with new dialog
    void signalSendMsgToDialog(QString sender, QString text);//for chat with one user

private slots:
    /// @brief represents the user had attempted connecting to server side more once time 
    void attemptConnection();
    /// @brief represents connecting the server
    void connectedToServer();
    /// @brief represents the user had attempted logingin more one time 
    /// @param userName name of user
    void attemptLogin(const QString &userName);
    /// @brief represents that the user loggedIn to the server
    void loggedIn();
    /// @brief represents that the user faild with connecting the server
    void loginFailed(const QString &reason);
    /// @brief represents the way to write received messages in chatModel from client side
    /// @param sender represents te user that send te message to the server firstly then the server pass it to the target client
    /// @param text 
    void messageReceived(const QString &sender, const QString &text);
    /// @brief represents the send message to all user it is called message broadcast
    void sendMessage();
    /// @brief represents that the user has missed connecting to the server and get an warning QMessageBox
    void disconnectedFromServer();
    /// @brief represents print an message in chatModel clarify via it that the user has already joined to the app
    /// @param username represents name of user
    void userJoined(const QString &username);
    /// @brief represents print an message in chatModel clarify via it that the user has already left to the app
    /// @param username represents name of user
    void userLeft(const QString &username);
    /// @brief represents failing in connect sockets such as NetworkError ..
    /// @param text represents type of error connecting sockets
    void error(QAbstractSocket::SocketError socketError);
    /// @brief represents that the user is online to the App
    /// @param users represents names of users that are online
    void reciveOnlineUsers(const QJsonArray &users);
    /// @brief that represents receiving a message from server with opening new dialog for the new unicast conversation
    /// @param senderVal name of user that the message will reach to you
    /// @param textVal represents the content of message
    void receiveMessageFromSpecificUser(QString senderVal,QString textVal);//for chat with one user
    /// @brief represents when the user want to chat with another user then he will select an user in list of online users then he this click to create dialog for unicast conversatin
    void on_ButtonChatOneUser_clicked();//for chat with one user
};

#endif // CHATWINDOW_H
