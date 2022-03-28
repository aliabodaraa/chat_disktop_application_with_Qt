#include "chatoneuser.h"
#include "ui_chatoneuser.h"

chatOneUser::chatOneUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatOneUser)
{
    ui->setupUi(this);
}

chatOneUser::~chatOneUser()
{
    delete ui;
}
