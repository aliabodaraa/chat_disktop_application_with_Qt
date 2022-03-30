#include "creategroupdialog.h"
#include "ui_creategroupdialog.h"

createGroupDialog::createGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createGroupDialog)
{
    ui->setupUi(this);
}

createGroupDialog::~createGroupDialog()
{
    delete ui;
}
