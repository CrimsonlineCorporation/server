#include "CLBattleServer.h"
#include <QJsonDocument>

CLBattleServer::CLBattleServer(const QString &host, const quint16 port, QObject *parent) :
    QObject(parent), tcpConnection(host, port, parent)
    {
    connect(&tcpConnection, &TCPConnection::connected, this, &CLBattleServer::writeData);
    connect(&tcpConnection, &TCPConnection::readyRead, this, &CLBattleServer::readData);

    worldAABB.lowerBound.Set(-200,-100);
    worldAABB.upperBound.Set( 200, 500);
    world.Step(0.1, 1, 1);
    }
void CLBattleServer::writeData()
    {
    QVariantMap battleServer;
    battleServer[QLatin1Literal("hello")] = QLatin1Literal("I don't know what I should send =(");
    QJsonDocument jsonDocument;
    jsonDocument.setObject(QJsonObject::fromVariantMap(battleServer));
    if(jsonDocument.isNull())
        qWarning() << "JSON serialize error";
    const QByteArray dataArrayUTF8 = jsonDocument.toJson();
    qDebug() << "writing :" << dataArrayUTF8;
    tcpConnection.write(dataArrayUTF8);
    }
void CLBattleServer::readData()
    {
    }
void CLBattleServer::createLive()
    {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    }
