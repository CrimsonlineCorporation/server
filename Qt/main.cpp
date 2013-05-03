#include <QCoreApplication>
#include "NetWork/CLBattleService.h"
#include <Box2D/Box2D.h>

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
    CLBattleService service(settings.value("adress","192.168.1.120").toString(),
                            settings.value("port",  "50000").toInt());
    service.connectServer();

    // Define world, gravity
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-200, -100);
    worldAABB.upperBound.Set(200, 500);
    b2World world(b2Vec2(0.0f, -10.0f));
    world.Step(0.1, 1, 1);
    return app.exec();
    }
