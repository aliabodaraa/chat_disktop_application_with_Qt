#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class createGroupDialog;
}

class createGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createGroupDialog(QWidget *parent = 0);
    ~createGroupDialog();

private:
    Ui::createGroupDialog *ui;
};

#endif // CREATEGROUPDIALOG_H
