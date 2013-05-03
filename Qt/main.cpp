#include <QCoreApplication>
#include "QtErrorMessageHandler.cpp"
#include "NetWork/CLService.h"

/*
 * main funct run #service for waiting Java server app
 */
int main(int argc, char *argv[])
    {
    QCoreApplication::setOrganizationName   (QLatin1Literal("CrimsonlineCorporation"));
    QCoreApplication::setApplicationName    (QLatin1Literal("Crimsonline"));
    QCoreApplication::setApplicationVersion (QLatin1Literal("0.0.1"));
    QCoreApplication::setOrganizationDomain (QLatin1Literal("https://github.com/CrimsonlineCorporation"));
    //change Q_ASSERT and qCritical abort to dialog
    qInstallMessageHandler(MessageHandler);
    qDebug() << QCoreApplication::applicationName() + QLatin1Literal(" starts.");
    QCoreApplication::addLibraryPath(QLatin1Literal("plugins"));

    QCoreApplication app(argc, argv);
    qsrand(QTime::currentTime().msec());
    QSettings settings("connect.ini", QSettings::IniFormat);
    settings.beginGroup("connect");

    CLService service(settings.value("adress","192.168.1.109").toString(),
                      settings.value("port",  "40000").toInt());
    service.start();
    return app.exec();
    }
