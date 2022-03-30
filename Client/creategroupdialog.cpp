#include "creategroupdialog.h"
#include "ui_creategroupdialog.h"

createGroupDialog::createGroupDialog(QWidget *parent,QVector<QString> vec, ChatClient* socket) :
    QDialog(parent),
    ui(new Ui::createGroupDialog),
    membersGrp(vec),
    socketClient(socket)
{
    ui->setupUi(this);
    for(int i=0;i<vec.length();i++){
        qDebug() << vec.at(i);
        membersGrp.append(vec.at(i));
       this->ui->listWidgetMemberGroup->addItem(membersGrp.at(i));
    }
}

createGroupDialog::~createGroupDialog()
{
    delete ui;
}
