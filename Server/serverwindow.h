#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>

namespace Ui {
class ServerWindow;
}
class ChatServer;
class ServerWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWindow)
public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
    ChatServer *m_chatServer;
private slots:
    /// @brief start server or stop it
    void toggleStartServer();
    /// @brief for write on window
    /// @param msg 
    void logMessage(const QString &msg);
};

#endif // SERVERWINDOW_H
