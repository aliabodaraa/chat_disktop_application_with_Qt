#include "chatoneuser.h"
#include "ui_chatoneuser.h"
#include "chatwindow.h"
#include "QCloseEvent"
#include "QMessageBox"
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

void chatOneUser::recieveMsgInDialog(QString sender, QString msg)
{
    ui->listWidgetInDailog->addItem(sender+":");
    ui->listWidgetInDailog->addItem(msg);
}

void chatOneUser::on_pushButton_clicked()
{
    socketClient->sendMessageToSelectedUser(ui->lineEdit->text(), this->targetUser);
    ui->listWidgetInDailog->addItem("me :");
    ui->listWidgetInDailog->addItem(ui->lineEdit->text());
    ui->lineEdit->setText("");
}
void chatOneUser::closeEvent(QCloseEvent *event)  // show prompt when user wants to close unicast conversation
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }

}
