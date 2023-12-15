#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMenu>
#include "servertrayicon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "zzz_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    QPixmap pixmap(32,32);
    pixmap.load(":/systemTrayIcon.png");
    QIcon icon(pixmap);

    ServerTrayIcon *trayIcon = new ServerTrayIcon(icon);
    qDebug() << trayIcon->isSystemTrayAvailable();
    trayIcon->buildContextMenu();
    trayIcon->setVisible(true);
    trayIcon->showMessage("Test Message", "Text", QSystemTrayIcon::Information, 1000);

    return a.exec();
}
