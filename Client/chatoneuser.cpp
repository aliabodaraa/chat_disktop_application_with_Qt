#include "chatoneuser.h"
#include "ui_chatoneuser.h"
#include "chatwindow.h"
chatOneUser::chatOneUser(QWidget *parent,QString userNameTarget, ChatClient* socket) :
    QDialog(parent),
    ui(new Ui::chatOneUser),
    targetUser(userNameTarget),
    socketClient(socket)
    {
        connect((ChatWindow *)parent , &ChatWindow::signalSendMsgToDialog, this, &chatOneUser::recieveMsgInDialog);
        ui->setupUi(this);
    }

chatOneUser::~chatOneUser()
{
    delete ui;
}


QString chatOneUser::getSelectedUser()
{
    return targetUser;
}

void chatOneUser::sendMessageFromDialog()
{
    socketClient->sendMessageToSelectedUser(ui->lineEdit->text(),this->targetUser);
    ui->listWidgetInDailog->addItem("From Me :");
    ui->listWidgetInDailog->addItem(ui->lineEdit->text());
    ui->lineEdit->setText("");
}

void chatOneUser::recieveMsgInDialog(QString sender, QString msg)
{
    ui->listWidgetInDailog->addItem(sender+":");
    ui->listWidgetInDailog->addItem(msg);
}

void chatOneUser::on_pushButton_clicked()
{
    this->sendMessageFromDialog();
}
