#include "CLBattleServer.h"
#include <QJsonDocument>

CLBattleServer::CLBattleServer(const QString &host, const quint16 port, QObject *parent) :
    TCPConnection(host, port, parent)
    {
    connect(&tcpSocket, &QTcpSocket::connected, this, &CLBattleServer::writeData);
    connect(&tcpSocket, &QTcpSocket::readyRead, this, &CLBattleServer::readData);
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
    tcpSocket.write(dataArrayUTF8);
    }
void CLBattleServer::readData()
    {
    }
