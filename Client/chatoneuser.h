#ifndef CHATONEUSER_H
#define CHATONEUSER_H
#include <QDialog>
#include "chatclient.h"
namespace Ui {
class chatOneUser;
}

class chatOneUser : public QDialog
{
    Q_OBJECT

public:
    /// @brief represents constructor for class chatOneUser that pass params for
    explicit chatOneUser(QWidget *parent = nullptr,QString userNameTarget=QStringLiteral("") , ChatClient* socket=0);
    ~chatOneUser();
    QString getSelectedUser();
private slots:
    /// @brief represents recieve message in priavte chat (Dialog)
    void recieveMsgInDialog(QString sender, QString text);
    /// @brief this method represents send message operation that i had selected from listWidget in chatWindow
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::chatOneUser *ui;
    /// @brief the trget user that i can currently send messages for he
    QString targetUser;
    /// @brief it represent socket from client side
    ChatClient *socketClient;
};

#endif // CHATONEUSER_H
