#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

#include <QDialog>
#include"QVector"
#include"chatclient.h"
namespace Ui {
class createGroupDialog;
}

class createGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createGroupDialog(QWidget *parent = nullptr,QVector<QString> vec={} , ChatClient* socket=0);
    ~createGroupDialog();

private:
    Ui::createGroupDialog *ui;
    QVector<QString> membersGrp;
    ChatClient *socketClient;
};

#endif // CREATEGROUPDIALOG_H
