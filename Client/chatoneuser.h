#ifndef CHATONEUSER_H
#define CHATONEUSER_H

#include <QDialog>

namespace Ui {
class chatOneUser;
}

class chatOneUser : public QDialog
{
    Q_OBJECT

public:
    explicit chatOneUser(QWidget *parent = 0);
    ~chatOneUser();

private:
    Ui::chatOneUser *ui;
};

#endif // CHATONEUSER_H
