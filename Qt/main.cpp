#include <QCoreApplication>
#include "NetWork/CLService.h"

/*
 * main funct run #service for waiting Java server app
 */
int main(int argc, char *argv[])
    {
    QCoreApplication app(argc, argv);
    qsrand(QTime::currentTime().msec());
    qDebug() << "Battle service starts";
    QSettings settings("connect.ini", QSettings::IniFormat);
    settings.beginGroup("connect");
    CLService service(settings.value("adress","192.168.1.120").toString(),
                            settings.value("port",  "50000").toInt());
    service.start();
    return app.exec();
    }
