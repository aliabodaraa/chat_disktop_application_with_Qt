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
    explicit chatOneUser(QWidget *parent = 0,QString userNameTarget="" , ChatClient* socket=0);
    ~chatOneUser();
    void sendMessageFromDialog();
    QString getSelectedUser();
private slots:
    void recieveMsgInDialog(QString sender, QString text);
    void on_pushButton_clicked();
private:
    Ui::chatOneUser *ui;
    QString targetUser;
    ChatClient *socketClient;
};

#endif // CHATONEUSER_H
