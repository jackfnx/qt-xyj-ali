#ifndef SERVERTRAYICON_H
#define SERVERTRAYICON_H

#include <QSystemTrayIcon>

class ServerTrayIcon: public QSystemTrayIcon
{
    Q_OBJECT
public:
    ServerTrayIcon(const QIcon &icon, QObject *parent=nullptr) : QSystemTrayIcon(icon, parent) {

    }

    void buildContextMenu();

private slots:
    void exitServer();
};

#endif // SERVERTRAYICON_H
