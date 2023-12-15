#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMenu>
#include <QHttpServer>
#include <QString>
#include "servertrayicon.h"

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(32,32);
    pixmap.load(":/systemTrayIcon.png");
    QIcon icon(pixmap);

    ServerTrayIcon *trayIcon = new ServerTrayIcon(icon);
    qDebug() << trayIcon->isSystemTrayAvailable();
    trayIcon->buildContextMenu();
    trayIcon->setVisible(true);
    trayIcon->showMessage("Test Message", "Text", QSystemTrayIcon::Information, 1000);

    QHttpServer httpServer;
    httpServer.route("/", []() {
        return "Hello world";
    });
    httpServer.route("/<arg>", [] (const QString cmd) {
        return u"Input: %1"_s.arg(cmd);
    });
    const auto port = httpServer.listen(QHostAddress::Any, 7013);
    qDebug() << port;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "zzz_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    return a.exec();
}
