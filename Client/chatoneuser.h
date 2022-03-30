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
