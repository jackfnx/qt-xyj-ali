#include "servertrayicon.h"
#include <QtCore/QCoreApplication>
#include <QAction>
#include <QMenu>

void ServerTrayIcon::exitServer() {
    this->hide();
    QCoreApplication::exit(0);
}

void ServerTrayIcon::buildContextMenu() {

    QAction *quitAction = new QAction("Quit", this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitServer()));

    QMenu *menu = new QMenu();
    menu->addAction(quitAction);

    this->setContextMenu(menu);
}
